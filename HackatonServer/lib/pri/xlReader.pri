win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../xlReader/release/ -lxlReader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../xlReader/debug/ -lxlReader

INCLUDEPATH += $$PWD/../xlReader
DEPENDPATH += $$PWD/../xlReader

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../xlReader/release/libxlReader.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../xlReader/debug/libxlReader.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../xlReader/release/xlReader.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../xlReader/debug/xlReader.lib
