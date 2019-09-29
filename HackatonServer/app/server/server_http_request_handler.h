#ifndef SERVER_HTTP_REQUEST_HANDLER_H
#define SERVER_HTTP_REQUEST_HANDLER_H

#include <functional>
#include <httpserver/httprequesthandler.h>


class ServerHttpRequestHandler final
    : public stefanfrings::HttpRequestHandler
{
  using WriteToLog  = std::function<void(const QString &)>;
  using Writed      = std::function<void(const QJsonObject &)>;
  using Readed      = std::function<void(const QJsonObject &)>;
public:
  explicit ServerHttpRequestHandler(QObject *parent = nullptr);
  ~ServerHttpRequestHandler() override;

private:
  void write(const QByteArray &array, stefanfrings::HttpRequest &request, stefanfrings::HttpResponse &response);

  // HttpRequestHandler interface
public:
  void service(stefanfrings::HttpRequest &request, stefanfrings::HttpResponse &response) override;

private:
  QJsonObject getQeryList() const;
  QJsonObject getFileById(const QString &id) const;
};

#endif // SERVER_HTTP_REQUEST_HANDLER_H
