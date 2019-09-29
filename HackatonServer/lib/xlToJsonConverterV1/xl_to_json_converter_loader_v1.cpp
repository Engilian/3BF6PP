#include "xl_to_json_converter_loader_v1.h"

#include "xl_to_json_converter_v1.h"
Q_DECLARE_METATYPE(xl::XlToJsonConverter::TaskP)
XlToJsonConverterLoaderV1::XlToJsonConverterLoaderV1(QObject *parent)
  : QObject (parent)
  , pf::FactoryPlugin ()
{
  regCreator<xl::XlToJsonConverter, xl::XlToJsonConverterV1>
      ( "xl::XlToJsonConverterV1", "xl::XlToJsonConverter" );
}

XlToJsonConverterLoaderV1::~XlToJsonConverterLoaderV1()
{

}

QString XlToJsonConverterLoaderV1::name() const
{
  return tr ( "XlToJsonConverterLoaderV1" );
}

QString XlToJsonConverterLoaderV1::briefInfo() const
{
  return tr ( "" );
}

QString XlToJsonConverterLoaderV1::author() const
{
  return "engilian@gmail.com";
}

QString XlToJsonConverterLoaderV1::version() const
{
  return "1.0";
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(xlToJsonConverterV1, XlToJsonConverterLoaderV1)
#endif // QT_VERSION < 0x050000
