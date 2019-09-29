win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/xlReader/release/ -lxlReader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/xlReader/debug/ -lxlReader

INCLUDEPATH += $$PWD/../../lib/xlReader
DEPENDPATH += $$PWD/../../lib/xlReader

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/xlReader/release/libxlReader.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/xlReader/debug/libxlReader.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/xlReader/release/xlReader.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/xlReader/debug/xlReader.lib
