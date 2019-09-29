#ifndef WIDGETGRAPTH_H
#define WIDGETGRAPTH_H

#include <QtCore>
#include <QWidget>
#include <QComboBox>
#include "graphmodifier.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QListWidget>
#include <QListWidgetItem>

class WidgetGrapth :public QWidget
{
    Q_OBJECT
public:
    WidgetGrapth(QWidget *parent = nullptr);
    void initInterface();
    void setJsonData( const QString &filePath );
    void setJsonData(const QByteArray &data );
private:
    GraphModifier *modifier;
    QComboBox *rangeList;
    QComboBox *rangeListByY;
    QNetworkAccessManager manager;
    QListWidget list;
    QStringList listId;
private slots:
    void onReply(QNetworkReply *reply);
    void onSelectGraph(QListWidgetItem *item);
};

#endif // WIDGETGRAPTH_H
