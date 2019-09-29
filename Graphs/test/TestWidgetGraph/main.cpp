#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <QDir>
#include "widgetgrapth.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile style( qApp->applicationDirPath() + "/style.css");
    style.open(QFile::ReadOnly);
    qApp->setStyleSheet(style.readAll());

    WidgetGrapth w;
    w.initInterface();




//    w.showFullScreen();
    w.show();

    return a.exec();
}
