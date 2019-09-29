#ifndef XL_READER_H
#define XL_READER_H

#include <memory>
#include <QObject>

namespace xl
{
  class XlTable;
  class XlReader
      : public QObject
  {
    Q_OBJECT
  public:
    using Table     = XlTable;
    using TableP    = std::shared_ptr<Table>;
    using TableList = QList<TableP>;
  protected:
    XlReader();
  public:
    virtual ~XlReader() override;

  public:
    virtual bool isOpen() const = 0;
    virtual TableP table(int index) const = 0;
    virtual TableP table(const QString &name) const = 0;
    virtual TableList tables() const = 0;
    virtual int count() const = 0;

  public slots:
    virtual bool open(const QString &path, QString *error) = 0;
    virtual void close() = 0;
  };
}



#endif // XL_READER_H
