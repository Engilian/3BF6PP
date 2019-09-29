#ifndef TASKS_WIDGET_H
#define TASKS_WIDGET_H

#include <QWidget>
#include <xl_to_json_converter_task.h>

namespace Ui {
  class TasksWidget;
}

class TasksWidget final
    : public QWidget
{
  Q_OBJECT
public:
  using Task  = xl::XlToJsonConverterTask;
  using TaskP = std::shared_ptr<Task>;
private:
  Ui::TasksWidget *ui;
public:
  explicit TasksWidget(QWidget *parent = nullptr);
  ~TasksWidget() override;

public slots:
  void add(const TaskP &task);

};

#endif // TASKS_WIDGET_H
