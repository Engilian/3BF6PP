#ifndef ITEMSFROMJSON_H
#define ITEMSFROMJSON_H

#include "graphitem.h"
#include <QList>

class ItemsFromJson
{
public:
    ItemsFromJson();

    static QList<GraphItem> fromJson(QString path);
    static QList<GraphItem> fromJson(const QByteArray &data);

    static QString tableTitle;
};

#endif // ITEMSFROMJSON_H
