#include "tasks_widget.h"
#include "ui_tasks_widget.h"
#include "task_process_widget.h"

TasksWidget::TasksWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TasksWidget)
{
  ui->setupUi(this);
}

TasksWidget::~TasksWidget()
{
  delete ui;
}

void TasksWidget::add(const TasksWidget::TaskP &task)
{
  auto w = new TaskProcessWidget( task );

  auto item = new QListWidgetItem();
  item->setSizeHint( QSize ( item->sizeHint().width(), w->sizeHint().height() ) );
  ui->content->addItem( item );
  ui->content->setItemWidget( item, w );
}
