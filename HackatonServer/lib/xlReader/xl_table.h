#ifndef XL_TABLE_H
#define XL_TABLE_H

#include <QObject>

namespace xl
{
  class XlTable
      : public QObject
  {
    Q_OBJECT
  protected:
    explicit XlTable();
  public:
    virtual ~XlTable() override;

  public:
    virtual QString name() const = 0;
    virtual int rowCount() const = 0;
    virtual int columnCount() const = 0;
    virtual int rowSpan(int row, int col) const = 0;
    virtual int colSpan(int row, int col) const = 0;
    virtual QVariant value(int row, int col) const = 0;
  };
}


#endif // XL_TABLE_H
