#ifndef SERVER_MW_H
#define SERVER_MW_H

#include <QMainWindow>
#include "httpserver/httplistener.h"
#include "server_http_request_handler.h"

namespace Ui {
  class ServerMw;
}

class ServerHttpRequestHandler;
class ServerMw final
    : public QMainWindow
{
  Q_OBJECT
  using Listener  = stefanfrings::HttpListener;
  using ListenerP = std::shared_ptr<Listener>;
  using Request   = ServerHttpRequestHandler;
  using RequestP  = std::shared_ptr<Request>;

  Ui::ServerMw  *ui;
  RequestP      request;
  ListenerP     listener;
public:
  explicit ServerMw(QWidget *parent = nullptr);
  ~ServerMw() override;

public slots:
  void importXl();

private slots:
  void initilizeHttp();
};

#endif // SERVER_MW_H
