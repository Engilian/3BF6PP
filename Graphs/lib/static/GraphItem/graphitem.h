#ifndef GRAPHITEM_H
#define GRAPHITEM_H

#include <QtCore>
#include <QVariant>
#include <QDoubleValidator>

struct Column
{
  QString caption;
  QVariant value;

  static bool isNumber(const QVariant &value)
  {
    int index;
    QString tmp = value.toString();
    QDoubleValidator v;
    return v.validate( tmp, index ) == QValidator::Acceptable;
  }

  bool operator < (const Column &rhs) const {
    if ( isNumber( value ) && isNumber( rhs.value ) )
      return value.toFloat() < rhs.value.toFloat();

    return value.toString() < rhs.value.toString();
  }

  bool operator >  (const Column &rhs) const {
    if ( isNumber( value ) && isNumber( rhs.value ) )
      return value.toFloat() > rhs.value.toFloat();
    return value.toString() > rhs.value.toString();
  }
};

struct GraphItem
{
  QString rowTitle;
  QList<Column> columns;

  GraphItem();
  float max() const;
};


#endif // GRAPHITEM_H
