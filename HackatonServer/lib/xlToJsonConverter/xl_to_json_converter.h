#ifndef XL_TO_JSON_CONVERTER_H
#define XL_TO_JSON_CONVERTER_H

#include <memory>
#include <QObject>

namespace xl
{
  class XlTable;
  class XlToJsonConverterTask;
  class XlToJsonConverter
      : public QObject
  {
    Q_OBJECT
  public:
    using Task      = XlToJsonConverterTask;
    using TaskP     = std::shared_ptr<Task>;
    using Table     = XlTable;
    using TableP    = std::shared_ptr<Table>;
    using TableList = QList<TableP>;
  protected:
    XlToJsonConverter();
  public:
    virtual ~XlToJsonConverter() override;

  public:
    virtual TaskP start(const QString &xlFile, const QString &tableName, const QString &outDir) const = 0;
  };
}


#endif // XL_TO_JSON_CONVERTER_H
