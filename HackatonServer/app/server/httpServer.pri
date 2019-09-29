win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../QtWebApp/QtWebApp/release/ -lQtWebApp1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../QtWebApp/QtWebApp/debug/ -lQtWebAppd1

INCLUDEPATH += $$PWD/../../../QtWebApp/QtWebApp
DEPENDPATH += $$PWD/../../../QtWebApp/QtWebApp
