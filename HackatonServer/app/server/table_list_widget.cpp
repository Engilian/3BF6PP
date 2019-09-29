#include "table_list_widget.h"
#include "ui_table_list_widget.h"

#include <xl_table.h>
#include <QMessageBox>

TableListWidget::TableListWidget(const ReaderP &reader)
  : QDialog()
  , ui(new Ui::TableListWidget)
  , reader ( reader )
{
  ui->setupUi(this);
}

TableListWidget::~TableListWidget()
{
  delete ui;
}

QStringList TableListWidget::selectedTables() const
{
  QStringList rezult;
  for ( auto item: ui->content->selectedItems() )
    rezult << item->text();
  return rezult;
}


void TableListWidget::showEvent(QShowEvent *event)
{
  ui->content->clear();
  for ( auto t: reader->tables() )
    ui->content->addItem( t->name() );
  QDialog::showEvent( event );
}

void TableListWidget::accept()
{
  if ( selectedTables().isEmpty() ) {
    QMessageBox::information( this
                              , tr ( "Внимание" )
                              , tr ( "Не выбрано ни одного листа для импорта." )
                              , tr ( "Ок" ) );
    return;
  }

  QDialog::accept();
}
