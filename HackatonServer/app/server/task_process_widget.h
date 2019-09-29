#ifndef TASK_PROCESS_WIDGET_H
#define TASK_PROCESS_WIDGET_H

#include <QWidget>
#include <xl_to_json_converter_task.h>

namespace Ui {
  class TaskProcessWidget;
}

class TaskProcessWidget final
    : public QWidget
{
  Q_OBJECT
public:
  using Task  = xl::XlToJsonConverterTask;
  using TaskP = std::shared_ptr<Task>;
private:
  Ui::TaskProcessWidget *ui;
  TaskP task;
public:
  explicit TaskProcessWidget(const TaskP &task);
  ~TaskProcessWidget() override;

private slots:
  void changed();
};

#endif // TASK_PROCESS_WIDGET_H
