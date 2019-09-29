#include "xl_to_json_converter_v1.h"
using namespace xl;
#include "xl_to_json_converter_task_v1.h"

XlToJsonConverterV1::XlToJsonConverterV1()
  : xl::XlToJsonConverter()
{

}

XlToJsonConverterV1::~XlToJsonConverterV1()
{

}


XlToJsonConverterV1::TaskP xl::XlToJsonConverterV1::start(const QString &xlFile, const QString &tableName, const QString &outDir) const
{
  return std::make_shared<XlToJsonConverterTaskV1>( xlFile, tableName, outDir );
}
