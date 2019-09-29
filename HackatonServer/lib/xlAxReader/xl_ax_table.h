#ifndef XL_AX_TABLE_H
#define XL_AX_TABLE_H

#include <QMap>
#include <QSize>
#include <QPoint>
#include <memory>
#include <xl_table.h>
#include <QAxObject>

class XlAxTable final
    : public xl::XlTable
{
  Q_OBJECT
public:
  using QAxObjectP  = std::shared_ptr<QAxObject>;

private:
  const QString                    _name;
  const QSize                      _size;
  QAxObjectP                       _sheet;
  mutable QMap<QString, QSize>     _cellsSpan;
  mutable QMap<QString, QVariant>  _cellsValue;
public:
  explicit XlAxTable(const QAxObjectP &obj);
  ~XlAxTable() override;

private slots:
  QString toStr(const QPoint &p) const;
  void updateCell(const QPoint &p) const;

  // XlTable interface
public:
  QString name() const override;
  int rowCount() const override;
  int columnCount() const override;
  int rowSpan(int row, int col) const override;
  int colSpan(int row, int col) const override;
  QVariant value(int row, int col) const override;
};

#endif // XL_AX_TABLE_H
