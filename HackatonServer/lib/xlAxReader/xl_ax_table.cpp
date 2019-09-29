#include "xl_ax_table.h"
#include <QSize>

namespace
{
  QSize getTableSize(const XlAxTable::QAxObjectP &obj) {
    auto range  = XlAxTable::QAxObjectP ( obj->querySubObject("UsedRange") );
    auto rows   = !!range
        ? XlAxTable::QAxObjectP ( range->querySubObject("Rows") )
        : XlAxTable::QAxObjectP ();
    auto cols   = !!range
        ? XlAxTable::QAxObjectP ( range->querySubObject("Columns") )
        : XlAxTable::QAxObjectP ();
    return QSize (
          ( !!cols ? cols->property("Count").toInt() : 0 )
          , ( !!rows ? rows->property("Count").toInt() : 0 ) );
  }
}

XlAxTable::XlAxTable(const QAxObjectP &obj)
  : xl::XlTable( )
  , _name ( obj->property("Name" ).toString() )
  , _size ( getTableSize( obj ) )
  , _sheet ( obj )
{

}

XlAxTable::~XlAxTable()
{
  _sheet.reset();
}

QString XlAxTable::toStr(const QPoint &p) const
{
  return QString( "%1,%2" ).arg( p.x() ).arg( p.y() );
}

void XlAxTable::updateCell(const QPoint &p) const
{
  auto cell = QAxObjectP ( _sheet->querySubObject("Cells(QVariant,QVariant)", p.x() + 1, p.y() + 1) );
  if ( !cell ) return;
  _cellsValue[ toStr( p ) ] = cell->property("Value").toString().remove( "\n\r" ).remove( "\n" );

  if ( cell->property( "MergeCells" ).toBool() ) {
    auto mergeCell = QAxObjectP ( cell->querySubObject( "MergeArea" ) );
    if ( mergeCell ) {
      auto mRows = QAxObjectP ( mergeCell->querySubObject( "Rows" ) );
      auto mCols = QAxObjectP ( mergeCell->querySubObject( "Columns" ) );
      if ( mRows && mCols ) {
        _cellsSpan[ toStr( p ) ] = QSize (
              std::max ( 1, mCols->dynamicCall( "Count()" ).toInt() )
              , std::max ( 1, mRows->dynamicCall( "Count()" ).toInt() ) );
      }
    }
  }
}


QString XlAxTable::name() const
{
  return _name;
}

int XlAxTable::rowCount() const
{
  return _size.height();
}

int XlAxTable::columnCount() const
{
  return _size.width();
}

int XlAxTable::rowSpan(int row, int col) const
{
  QPoint p( row, col );
  auto key = toStr( p );
  if ( !_cellsSpan.contains( key ) )
    updateCell( p );
  return _cellsSpan.value( key ).height();
}

int XlAxTable::colSpan(int row, int col) const
{
  QPoint p( row, col );
  auto key = toStr( p );
  if ( !_cellsSpan.contains( key ) )
    updateCell( p );

  return _cellsSpan.value( key ).width();
}

QVariant XlAxTable::value(int row, int col) const
{
  QPoint p( row, col );
  auto key = toStr( p );
  if ( !_cellsValue.contains( key ) )
    updateCell( p );

  return _cellsValue.value( key );
}
