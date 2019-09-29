#include "server_mw.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ServerMw w;
  w.show();

  return a.exec();
}
