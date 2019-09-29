#include "task_process_widget.h"
#include "ui_task_process_widget.h"

TaskProcessWidget::TaskProcessWidget(const TaskP &task)
  : QWidget()
  , ui(new Ui::TaskProcessWidget)
  , task ( task )
{
  ui->setupUi(this);
  ui->title->setText( task->tableName() );

  connect( task.get(),  &Task::finished,
           this,        &TaskProcessWidget::changed );

  connect( task.get(),  &Task::progressChanged,
           this,        &TaskProcessWidget::changed );

  changed();
}

TaskProcessWidget::~TaskProcessWidget()
{
  delete ui;
}

void TaskProcessWidget::changed()
{
  if ( task->isRunning() ) {
    ui->progress->setValue( static_cast<int>( std::round(  ui->progress->maximum() * task->progress() ) ) );
  } else if ( task->status() ) {
    ui->title->setText( task->tableName() + " - завершено" );
    ui->progress->setValue( ui->progress->maximum() );
  } else {
    ui->title->setText( task->tableName() + " - ошибка" );
    ui->title->setToolTip( task->errorString() );
  }
}
