#ifndef TABLE_LIST_WIDGET_H
#define TABLE_LIST_WIDGET_H

#include <QDialog>
#include <xl_reader.h>

namespace Ui {
  class TableListWidget;
}

class TableListWidget : public QDialog
{
  Q_OBJECT
public:
  using Reader  = xl::XlReader;
  using ReaderP = std::shared_ptr<Reader>;

private:
  Ui::TableListWidget *ui;
  ReaderP reader;
public:
  explicit TableListWidget(const ReaderP &reader);
  ~TableListWidget() override;

public:
  QStringList selectedTables() const;

  // QWidget interface
protected:
  void showEvent(QShowEvent *event) override;

  // QDialog interface
public slots:
  void accept() override;
};

#endif // TABLE_LIST_WIDGET_H
