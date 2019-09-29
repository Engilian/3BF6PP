QT          -= gui

TARGET      = xlToJsonConverter
TEMPLATE    = lib
CONFIG      += c++11
CONFIG      += staticlib

SOURCES += \
        xl_to_json_converter.cpp \
    xl_to_json_converter_task.cpp

HEADERS += \
        xl_to_json_converter.h \
    xl_to_json_converter_task.h

