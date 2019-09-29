#include "server_http_request_handler.h"

#include <QDir>
#include <QObject>
#include <iostream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QCoreApplication>

ServerHttpRequestHandler::ServerHttpRequestHandler(QObject *parent)
  : stefanfrings::HttpRequestHandler( parent )
{

}

ServerHttpRequestHandler::~ServerHttpRequestHandler()
{

}

void ServerHttpRequestHandler::write(const QByteArray &array, stefanfrings::HttpRequest &, stefanfrings::HttpResponse &response)
{
  response.write ( array );
  std::cout << "<<<<" << QString::fromUtf8( array ).toStdString() << std::endl;
}


void ServerHttpRequestHandler::service(stefanfrings::HttpRequest &request
                                       , stefanfrings::HttpResponse &response)
{ 
  QJsonParseError error;
  auto body = request.getBody();
  std::cout << ">>>>" << QString::fromUtf8( body ).toStdString() << std::endl;
  auto doc = QJsonDocument::fromJson( body, &error );
  if ( error.error != QJsonParseError::NoError ) {
    QJsonObject obj;
    obj[ "error" ]    = error.errorString();
    obj[ "message" ]  = "Posol v zopu!";
    return write ( QJsonDocument( obj ).toJson(), request, response );
  }

  auto type = doc.object()[ "type" ].toString();
  if ( type == "get_list" ) {
    return write( QJsonDocument ( getQeryList() ).toJson(), request, response );
  } else if ( type == "get_data" ) {
    return write( QJsonDocument ( getFileById( doc.object()[ "id" ].toString() ) ).toJson(), request, response );
  }

  QJsonObject obj;
  obj[ "error" ] = "invalid type";
  return write( QJsonDocument( obj ).toJson(), request, response );
}

QJsonObject ServerHttpRequestHandler::getQeryList() const
{
  const QString diretoryPath = QDir::fromNativeSeparators(
        QCoreApplication::applicationDirPath() + "\\db\\import\\" );
  QDir directory ( diretoryPath );

  QJsonArray array;
  for ( auto &name: directory.entryList() ) {
    QFile f ( directory.absoluteFilePath( directory.absoluteFilePath( name ) ) );
    if ( f.open( QIODevice::ReadOnly ) ) {
      QJsonParseError error;
      auto doc = QJsonDocument::fromJson( f.readAll(), &error );
      f.close();
      if ( error.error == QJsonParseError::NoError ) {
          QJsonObject obj;
          obj[ "id" ] = QFileInfo ( directory.absoluteFilePath( name ) ).baseName();
          obj[ "name" ] = doc.object()[ "Title" ].toString();
          array.append( obj );
      }
    }
  }



  QJsonObject obj;
  obj["type"] = "get_list";
  obj[ "data" ] = array;
  return obj;
}

QJsonObject ServerHttpRequestHandler::getFileById(const QString &id) const
{
  QJsonObject out;
  out[ "type" ] = "get_data";
  const QString diretoryPath = QDir::fromNativeSeparators(
        QCoreApplication::applicationDirPath() + "\\db\\import\\" );
  QDir directory ( diretoryPath );

  QFile f ( directory.absoluteFilePath( directory.absoluteFilePath( id + ".json" ) ) );
  if ( f.open( QIODevice::ReadOnly ) ) {
    QJsonParseError error;
    auto doc = QJsonDocument::fromJson( f.readAll(), &error );
    f.close();
    if ( error.error == QJsonParseError::NoError ) {
        out[ "data" ] = doc.object();
    }
  }

  return out;
}
