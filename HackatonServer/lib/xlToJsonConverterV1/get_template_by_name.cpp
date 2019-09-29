#include "get_template_by_name.h"
using namespace xl;

#include <QDir>
#include <QFile>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QCoreApplication>

GetTemplateByName::GetTemplateByName()
{

}

QJsonObject GetTemplateByName::get(const QString &name)
{
  QDir directory ( QDir::fromNativeSeparators( QCoreApplication::applicationDirPath() + "/templates" ) );
  for ( auto &n: directory.entryList( { "*.json" }, QDir::Files ) ) {
    QFile f ( directory.absoluteFilePath( n ) );
    if ( f.open( QIODevice::ReadOnly ) ) {
      QJsonParseError err;
      auto doc = QJsonDocument::fromJson( f.readAll(), &err );
      f.close();

      if ( err.error == QJsonParseError::NoError ) {
        auto obj = doc.object();
        if ( obj[ "id" ] == name )
          return obj;
      }
    }
  }

  return QJsonObject();
}
