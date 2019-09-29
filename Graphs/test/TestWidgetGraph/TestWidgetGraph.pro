QT += gui widgets datavisualization network

TEMPLATE = app

CONFIG += c++11
CONFIG -= app_bundle

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/static/WidgetGrapth/release/ -lWidgetGrapth
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/static/WidgetGrapth/debug/ -lWidgetGrapth
else:unix: LIBS += -L$$OUT_PWD/../../lib/static/WidgetGrapth/ -lWidgetGrapth

INCLUDEPATH += $$PWD/../../lib/static/WidgetGrapth
DEPENDPATH += $$PWD/../../lib/static/WidgetGrapth

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/WidgetGrapth/release/libWidgetGrapth.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/WidgetGrapth/debug/libWidgetGrapth.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/WidgetGrapth/release/WidgetGrapth.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/WidgetGrapth/debug/WidgetGrapth.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../lib/static/WidgetGrapth/libWidgetGrapth.a
###
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
