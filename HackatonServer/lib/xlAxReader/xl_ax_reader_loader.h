#ifndef XL_AX_READER_LOADER_H
#define XL_AX_READER_LOADER_H

#include <QObject>
#include <factory_plugin/factory_plugin.h>


class XlAxReaderLoader final
    : public QObject
    , public pf::FactoryPlugin
{
  Q_OBJECT
  Q_INTERFACES (psys::IPlugin)
#if QT_VERSION >= 0x050000
  Q_PLUGIN_METADATA(IID FACTORY_PLUGIN_VALID_STRING FILE "xlAxReader.json")
#endif // QT_VERSION >= 0x050000

public:
  XlAxReaderLoader(QObject *parent = 0);
  ~XlAxReaderLoader() override;

  // IPlugin interface
public:
  virtual QString name() const override;
  virtual QString briefInfo() const override;
  virtual QString author() const override;
  virtual QString version() const override;
};

#endif // XL_AX_READER_LOADER_H
