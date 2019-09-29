#include "graphitem.h"
#include <algorithm>

GraphItem::GraphItem()
{
}

float GraphItem::max() const
{
  auto copy = columns;
  if ( copy.count() > 0 ) {
    auto res = std::max_element(copy.begin(), copy.end());
    return res->value.toFloat();
  }
  return 0.0;
}
