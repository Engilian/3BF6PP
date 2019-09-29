#include "xl_ax_reader.h"
#include "xl_ax_table.h"

#include <QDir>

XlAxReader::XlAxReader()
  : xl::XlReader()
{

}

XlAxReader::~XlAxReader()
{
  close();
}


bool XlAxReader::isOpen() const
{
  return !!_excel;
}

XlAxReader::TableP XlAxReader::table(int index) const
{
  return _tables.at( index );
}

XlAxReader::TableP XlAxReader::table(const QString &name) const
{
  for ( auto &t: _tables )
    if ( t->name() == name )
      return t;
  return TableP();
}

XlAxReader::TableList XlAxReader::tables() const
{
  return _tables;
}

int XlAxReader::count() const
{
  return _tables.count();
}

bool XlAxReader::open(const QString &path, QString *error)
{
  if ( !isOpen() ) {
    _excel = std::make_shared<QAxObject>( "Excel.Application", nullptr );
//    _excel->Ini
    _workbooks = QAxObjectP ( _excel->querySubObject("Workbooks") );
    if ( _workbooks ) {
      _workbook = QAxObjectP ( _workbooks->querySubObject("Open(const QString&)", QDir::fromNativeSeparators( path ) ) );
      if ( _workbook ) {
        _sheets = QAxObjectP ( _workbook->querySubObject("Worksheets") );
        if ( _sheets ) {

          const int listCount = _sheets->property("Count").toInt();
          for ( int i = 0; i < listCount; ++i ) {
              auto sheet = QAxObjectP ( _sheets->querySubObject("Item(int)", i + 1) );
              if ( sheet )
                _tables << std::make_shared<XlAxTable>( sheet );
          }
          return true;
        }
      }
    }
  }

  if ( error )
    *error = tr ( "System error" );

  return false;
}

void XlAxReader::close()
{
  _tables.clear();
  _sheets.reset();
  _workbook.reset();
  _workbooks.reset();

  if ( _excel )
    _excel->dynamicCall("Quit(void)");
  _excel.reset();
}
