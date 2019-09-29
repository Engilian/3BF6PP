#ifndef XL_TO_JSON_CONVERTER_V1_H
#define XL_TO_JSON_CONVERTER_V1_H

#include <xl_to_json_converter.h>

namespace xl
{
  class XlToJsonConverterV1 final
      : public xl::XlToJsonConverter
  {
    Q_OBJECT
  public:
    explicit XlToJsonConverterV1();
    ~XlToJsonConverterV1() override;

    // XlToJsonConverter interface
  public:
    TaskP start(const QString &xlFile, const QString &tableName, const QString &outDir) const override;
  };
}


#endif // XL_TO_JSON_CONVERTER_V1_H
