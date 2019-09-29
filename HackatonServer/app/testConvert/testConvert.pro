QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle
DESTDIR = ../../bin

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/xlToJsonConverter/release/ -lxlToJsonConverter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/xlToJsonConverter/debug/ -lxlToJsonConverter

INCLUDEPATH += $$PWD/../../lib/xlToJsonConverter
DEPENDPATH += $$PWD/../../lib/xlToJsonConverter

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/xlToJsonConverter/release/libxlToJsonConverter.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/xlToJsonConverter/debug/libxlToJsonConverter.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/xlToJsonConverter/release/xlToJsonConverter.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/xlToJsonConverter/debug/xlToJsonConverter.lib




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
