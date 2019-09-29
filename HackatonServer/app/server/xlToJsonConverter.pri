win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/xlToJsonConverter/release/ -lxlToJsonConverter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/xlToJsonConverter/debug/ -lxlToJsonConverter

INCLUDEPATH += $$PWD/../../lib/xlToJsonConverter
DEPENDPATH += $$PWD/../../lib/xlToJsonConverter

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/xlToJsonConverter/release/libxlToJsonConverter.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/xlToJsonConverter/debug/libxlToJsonConverter.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/xlToJsonConverter/release/xlToJsonConverter.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/xlToJsonConverter/debug/xlToJsonConverter.lib
