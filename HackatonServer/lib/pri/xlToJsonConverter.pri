win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../xlToJsonConverter/release/ -lxlToJsonConverter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../xlToJsonConverter/debug/ -lxlToJsonConverter

INCLUDEPATH += $$PWD/../xlToJsonConverter
DEPENDPATH += $$PWD/../xlToJsonConverter

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../xlToJsonConverter/release/libxlToJsonConverter.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../xlToJsonConverter/debug/libxlToJsonConverter.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../xlToJsonConverter/release/xlToJsonConverter.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../xlToJsonConverter/debug/xlToJsonConverter.lib
