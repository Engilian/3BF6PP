#INCLUDEPATH += ../../../include

#LIBS += -L$$OUT_PWD/../../../lib

TEMPLATE = app

QT += datavisualization

target.path = $$[QT_INSTALL_EXAMPLES]/datavisualization/$$TARGET
INSTALLS += target


SOURCES += main.cpp graphmodifier.cpp
HEADERS += graphmodifier.h

QT += widgets
requires(qtConfig(fontcombobox))
requires(qtConfig(combobox))

OTHER_FILES += doc/src/* \
               doc/images/*

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/static/GraphItem/release/ -lGraphItem
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/static/GraphItem/debug/ -lGraphItem
else:unix: LIBS += -L$$OUT_PWD/../../lib/static/GraphItem/ -lGraphItem

INCLUDEPATH += $$PWD/../../lib/static/GraphItem
DEPENDPATH += $$PWD/../../lib/static/GraphItem

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/GraphItem/release/libGraphItem.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/GraphItem/debug/libGraphItem.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/GraphItem/release/GraphItem.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/GraphItem/debug/GraphItem.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/GraphItem/libGraphItem.a
