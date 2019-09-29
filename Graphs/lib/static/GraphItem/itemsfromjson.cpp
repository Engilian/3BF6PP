#include "itemsfromjson.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

ItemsFromJson::ItemsFromJson()
{

}

QList<GraphItem> ItemsFromJson::fromJson(QString path)
{
    QFile jsonFile(path);
    if (!jsonFile.open(QIODevice::ReadOnly))
    {
        qDebug( ) << "Error on open file:" <<path;
        return  QList<GraphItem>();
    }
    return fromJson(jsonFile.readAll());
}

QString ItemsFromJson::tableTitle;

QList<GraphItem> ItemsFromJson::fromJson(const QByteArray &data)
{
    QList<GraphItem> result;
    QJsonParseError errorPtr;
    QJsonDocument jdoc = QJsonDocument::fromJson(data, &errorPtr);
    if (jdoc.isNull()) {
        qDebug() << "Parse failed";
    }

    auto list = jdoc.object().value("data").toObject().value("Rows").toArray();
    ItemsFromJson::tableTitle = jdoc.object().value("Title").toString();
    for (int i=0;i<list.count();++i) {
        auto itemObj = list[i].toObject();
        GraphItem itm;
        itm.rowTitle =itemObj.value("Row").toString();
        auto colsObj = itemObj.value("Columns").toArray();
        for (auto it: colsObj){
            Column col;
            col.caption = it.toObject().value("Caption").toString();
            col.value = it.toObject().value("Value").toString();
            itm.columns.append(col);
        }
        std::sort( itm.columns.begin(), itm.columns.end(), [](const Column &c1, const Column &c2) {
          return c1.caption < c2.caption;
        });
        result.append(itm);
    }

    return result;
}
