#include "xl_to_json_converter_thread_v1.h"
using namespace xl;

#include <QDir>
#include <QFile>
#include <QRect>
#include <thread>
#include <QJsonArray>
#include <xl_table.h>
#include <xl_reader.h>
#include <QJsonDocument>
#include <QCoreApplication>
#include <pfactory/pfactory.h>
#include "get_template_by_name.h"
#include "xl_to_json_converter_task_v1.h"

#include <Windows.h>

XlToJsonConverterThreadV1::XlToJsonConverterThreadV1(XlToJsonConverterTaskV1 *obj)
  : QThread ()
  , event ( obj )
  , _progress ( 0.0 )
  , _status ( false )
  , _isRun ( true )
  , _isAbort ( false )
{

}

XlToJsonConverterThreadV1::~XlToJsonConverterThreadV1()
{
  if ( isRunning() )
    abort();
}

bool XlToJsonConverterThreadV1::status() const
{
  return _status.load();
}

bool XlToJsonConverterThreadV1::isRunning() const
{
  return _isRun.load();
}

double XlToJsonConverterThreadV1::progress() const
{
  return _progress.load();
}

QString XlToJsonConverterThreadV1::errorString() const
{
  return _error;
}

void XlToJsonConverterThreadV1::abort()
{
  while ( _isRun.load() ) {
    _isAbort.store( true );
    std::this_thread::sleep_for ( std::chrono::milliseconds ( 20 ) );
  }
}

XlToJsonConverterThreadV1::ReaderP XlToJsonConverterThreadV1::createReader() const
{
  try {
    pf::PFactoryExp::inst()->add<xl::XlReader>( "xl::XlReader" );
  } catch (...) { }

  try {
    return ReaderP ( pf::PFactoryExp::inst()->create<xl::XlReader>() );
  } catch (...) { }

  return ReaderP();
}

QRect XlToJsonConverterThreadV1::getRowRect(const XlToJsonConverterThreadV1::TableP &table, const QJsonObject &tableTemplate) const
{
  int row     = tableTemplate[ "row" ].toObject()[ "start_row" ].toVariant().toInt();
  int column  = tableTemplate[ "row" ].toObject()[ "start_column" ].toVariant().toInt();
  return QRect ( column, row, 1, table->rowCount() );
}

#include <QIntValidator>
QRect XlToJsonConverterThreadV1::getColumnRect(const TableP &table, const QJsonObject &tableTemplate) const
{
  auto findColumn = [](int row, int column, const QString &text, const TableP &table)->QRect {
    for ( int i = 0; i < table->columnCount(); ++i ) {
      if ( table->value( row - 1, i ).toString().trimmed() == text.trimmed() ) {
        auto columnSpan = table->colSpan( row - 1, i );
        return QRect ( i, row, columnSpan, 1 );
      }
    }
    return QRect ( column, row, 0, 0 );
  };

  int row     = tableTemplate[ "column" ].toObject()[ "start_row" ].toVariant().toInt();
  int column  = 0;
  int end     = table->columnCount();
  auto endSource = tableTemplate[ "column" ].toObject()[ "end" ].toString();
  auto columnSource = tableTemplate[ "column" ].toObject()[ "start_column" ].toString();

  int tmp;
  QIntValidator v;
  if  ( v.validate( columnSource, tmp ) == QValidator::State::Acceptable ) {
    column = QVariant ( columnSource ).toInt();
  } else {
    auto r = findColumn ( row, 0, columnSource.remove( "head:" ), table );
    column = r.x();
    row = r.y();
  }

  if  ( v.validate( endSource, tmp ) == QValidator::State::Acceptable ) {
    end = QVariant ( endSource ).toInt();
    if ( end < 0 )
      end = table->columnCount();
  } else {
    auto r = findColumn ( row, column, columnSource.remove( "head:" ), table );
    end = r.right();
    row = r.y();
  }

  return QRect ( column, row, end, 1 );
}

QJsonObject XlToJsonConverterThreadV1::getRowObject(int row
                                                    , const QRect &rowRect
                                                    , const QRect &columnRect
                                                    , const XlToJsonConverterThreadV1::TableP &table
                                                    , const QJsonObject &tableTamplate) const
{
  auto value = table->value( row, rowRect.x() ).toString();
  if ( tableTamplate[ "row" ].toObject()[ "type" ] == "area" ) {
    auto list = getAreaList( tableTamplate[ "row" ].toObject()[ "level" ].toVariant().toInt()
        , tableTamplate[ "row" ].toObject()[ "depth" ].toVariant().toInt() );
    if ( !list.contains( value ) )
      return  QJsonObject();
  }

  if ( !value.isEmpty() ) {
    QJsonObject obj;
    obj[ "Row" ] = table->value( row, rowRect.x() ).toString();
    QJsonArray data;
    for ( int j = columnRect.x(); j < columnRect.right(); ++j ) {
      auto tmp = getColumnObject( row, j, columnRect, table, tableTamplate );
      if ( !tmp.isEmpty() )
        data.append( tmp );
    }
    obj[ "Columns" ] = data;
    return obj;
  }
  return QJsonObject();
}

QJsonObject XlToJsonConverterThreadV1::getColumnObject(int row, int column, const QRect &columnRect, const XlToJsonConverterThreadV1::TableP &table, const QJsonObject &tableTamplate) const
{
  if ( !table->value( columnRect.y(), column ).toString().isEmpty() ) {
    if ( tableTamplate[ "column" ].toObject()[ "type" ] == "int" ) {
      QIntValidator v; int tmp;
      auto value = table->value( columnRect.y(), column ).toString();
      if ( v.validate( value, tmp ) != QValidator::Acceptable )
        return QJsonObject();
    } else if ( tableTamplate[ "column" ].toObject()[ "type" ] == "number" ) {
      QDoubleValidator v; int tmp;
      auto value = table->value( columnRect.y(), column ).toString();
      if ( v.validate( value, tmp ) != QValidator::Acceptable )
        return QJsonObject();
    }

    if ( columnRect.height() > 1 ) {

    } else if ( columnRect.height( ) == 1 ) {
      QJsonObject obj;
      obj[ "Caption" ] = table->value( columnRect.y(), column ).toString();
      obj[ "Value" ] = table->value( row, column ).toString();
      return obj;
    }
  }

  return QJsonObject();
}

void XlToJsonConverterThreadV1::runDo(const TableP &table, const QJsonObject &tableTemplate)
{
  _progress = 0.0;
  event->progressChanged();
  QCoreApplication::processEvents();

  auto arr = tableTemplate[ "template" ].toArray();
  double stepProgres = !arr.isEmpty()
      ? ( 1.0 - _progress ) / arr.count()
      : 1.0;

  for ( int i = 0; i < arr.count() && !_isAbort.load(); ++i ) {
    if ( arr.at( i ).isObject() )
      runDoItem( table, arr.at( i ).toObject(), stepProgres );
  }
  _progress = 1.0;
  event->progressChanged();
  QCoreApplication::processEvents();
}

void XlToJsonConverterThreadV1::runDoItem(const XlToJsonConverterThreadV1::TableP &table, const QJsonObject &tableTemplate, double progress)
{
  auto rowRect    = getRowRect( table, tableTemplate );
  auto columnRect = getColumnRect( table, tableTemplate );

  double saveProgressValue = progress * 0.1;
  double step = ( progress - saveProgressValue ) / rowRect.height();

  QJsonArray arr;

  for ( int row = rowRect.y(); row < rowRect.y() + rowRect.height() && row < table->rowCount(); ++row ) {
    auto obj = getRowObject( row, rowRect, columnRect, table, tableTemplate );
    _progress = _progress + step;
    event->progressChanged();
    QCoreApplication::processEvents();
    if ( obj.isEmpty() ) continue;
    arr.append( obj );
  }

  auto out = tableTemplate[ "out" ].toString();
  if ( !out.isEmpty() ) {
    QDir dir ( QDir::fromNativeSeparators( QCoreApplication::applicationDirPath() + "/db/import/" ) );
    if ( !dir.exists() )
      dir.mkpath( "." );

    QFile f ( dir.absoluteFilePath( out + ".json" ) );
    if ( f.open( QIODevice::WriteOnly ) ) {
      QJsonObject obj;
      obj[ "id" ] = tableTemplate[ "out" ];
      obj[ "Title" ] = tableTemplate[ "name" ];
      obj[ "Rows" ] = arr;
      QJsonDocument doc ( obj );
      f.write( doc.toJson() );
      f.close();
    } else {
      _error = tr ( "Error import: permission danied" );
    }

  } else {
    _error = tr ( "Eror save imported data: out file is ismpty" );
  }
}

QStringList XlToJsonConverterThreadV1::getAreaList(int level, int depth) const
{
  const QString path = QDir::fromNativeSeparators(
        QCoreApplication::applicationDirPath() + "/types/area.json" );
  QFile f ( path );
  if ( f.open( QIODevice::ReadOnly ) ) {
    QJsonParseError error;
    auto areaArrays = QJsonDocument::fromJson( f.readAll(), &error ).object()[ "tree" ].toArray();
    if ( error.error == QJsonParseError::NoError ) {
      std::function<QStringList(const QJsonObject &obj, int level, int depth, int currentLevel)> getList =
          [&getList](const QJsonObject &obj, int level, int depth, int currentLevel)->QStringList {
        QStringList rezult;

        if ( currentLevel >= level && currentLevel < level + depth )
          rezult.append( obj[ "name" ].toString() );

        // Handle chailds
        if ( obj.contains( "child" ) ? obj[ "child" ].isArray() : false ) {
          if ( currentLevel + 1 < level + depth ) {
            auto arr = obj[ "child" ].toArray();
            for ( int i = 0; i < arr.count(); ++i ) {
              rezult.append( getList ( arr.at( i ).toObject(), level, depth, currentLevel + 1 ) );
            }
          }
        }

        return rezult;
      };

      QStringList rezults;
      for ( int i = 0; i < areaArrays.count(); ++i ) {
        rezults.append( getList ( areaArrays.at( i ).toObject(), level, depth, 0 ) );
      }
      return rezults;
    }
  }

  return QStringList();
}


void xl::XlToJsonConverterThreadV1::run()
{
  _isRun.store( true );
  _isAbort.store( false );
  _status.store( false );
  _progress = 0.0;

  CoInitializeEx(NULL, COINIT_MULTITHREADED);

  auto reader = createReader();
  if ( reader ) {
    if ( reader->open( event->_xlFile, &_error ) ) {
      auto table = reader->table( event->_tableName );
      if ( table ) {
        auto tableTamplate = GetTemplateByName::get( table->name() );
        if ( !tableTamplate.isEmpty() ) {
          runDo( table, tableTamplate );
          _status = true;
        } else {
          _error = tr ( "Cannot find template for table %1" ).arg( event->_tableName );
        }
      } else {
        _error = tr ( "Cannot find table %1" ).arg( event->_tableName );
      }
    }
  } else {
    _error = tr ( "Error create reader xl files" );
  }

  event->finished();
  _isRun.store( false );
  _isAbort.store( false );
}
