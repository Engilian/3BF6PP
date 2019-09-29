#include "xl_ax_reader_loader.h"

#include <xl_ax_reader.h>
XlAxReaderLoader::XlAxReaderLoader(QObject *parent)
  : QObject (parent)
  , pf::FactoryPlugin ()
{
  regCreator<xl::XlReader, XlAxReader>
      ( "XlAxReader", "xl::XlReader" );
}

XlAxReaderLoader::~XlAxReaderLoader()
{

}

QString XlAxReaderLoader::name() const
{
  return tr ( "XlAxReader" );
}

QString XlAxReaderLoader::briefInfo() const
{
  return tr ( "" );
}

QString XlAxReaderLoader::author() const
{
  return "engilian@gmail.com";
}

QString XlAxReaderLoader::version() const
{
  return "1.0";
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(xlAxReader, XlAxReaderLoader)
#endif // QT_VERSION < 0x050000
