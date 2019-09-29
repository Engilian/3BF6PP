#ifndef XL_TO_JSON_CONVERTER_LOADER_V1_H
#define XL_TO_JSON_CONVERTER_LOADER_V1_H

#include <QObject>
#include <factory_plugin/factory_plugin.h>


class XlToJsonConverterLoaderV1 final
    : public QObject
    , public pf::FactoryPlugin
{
  Q_OBJECT
  Q_INTERFACES (psys::IPlugin)
#if QT_VERSION >= 0x050000
  Q_PLUGIN_METADATA(IID FACTORY_PLUGIN_VALID_STRING FILE "xlToJsonConverterV1.json")
#endif // QT_VERSION >= 0x050000

public:
  XlToJsonConverterLoaderV1(QObject *parent = 0);
  ~XlToJsonConverterLoaderV1() override;

  // IPlugin interface
public:
  virtual QString name() const override;
  virtual QString briefInfo() const override;
  virtual QString author() const override;
  virtual QString version() const override;
};

#endif // XL_TO_JSON_CONVERTER_LOADER_V1_H
