#ifndef GET_TEMPLATE_BY_NAME_H
#define GET_TEMPLATE_BY_NAME_H

#include <QJsonObject>

namespace xl
{
  class GetTemplateByName
  {
    explicit GetTemplateByName();
  public:
    static QJsonObject get(const QString &name);
  };
}



#endif // GET_TEMPLATE_BY_NAME_H
