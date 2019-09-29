win32: LIBS += -L$$OUT_PWD/../../../PluginFactory/src/libs/Factory/bin/ -lFactory

INCLUDEPATH += $$PWD/../../../PluginFactory/src/libs/Factory
DEPENDPATH += $$PWD/../../../PluginFactory/src/libs/Factory

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../../PluginFactory/src/libs/Factory/bin/Factory.lib
else:win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../../PluginFactory/src/libs/Factory/bin/libFactory.a

win32: LIBS += -L$$OUT_PWD/../../../PluginFactory/src/libs/FactoryPlugin/bin/ -lFactoryPlugin

INCLUDEPATH += $$PWD/../../../PluginFactory/src/libs/FactoryPlugin
DEPENDPATH += $$PWD/../../../PluginFactory/src/libs/FactoryPlugin

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../../PluginFactory/src/libs/FactoryPlugin/bin/FactoryPlugin.lib
else:win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../../PluginFactory/src/libs/FactoryPlugin/bin/libFactoryPlugin.a

win32: LIBS += -L$$OUT_PWD/../../../PluginFactory/src/libs/PluginSystem/bin/ -lPluginSystem

INCLUDEPATH += $$PWD/../../../PluginFactory/src/libs/PluginSystem
DEPENDPATH += $$PWD/../../../PluginFactory/src/libs/PluginSystem

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../../PluginFactory/src/libs/PluginSystem/bin/PluginSystem.lib
else:win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../../PluginFactory/src/libs/PluginSystem/bin/libPluginSystem.a
