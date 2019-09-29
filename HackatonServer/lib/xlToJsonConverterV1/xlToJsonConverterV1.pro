QT          += core gui

TARGET      = xlToJsonConverterV1
TEMPLATE    = lib
CONFIG      += plugin
CONFIG      += c++11
DESTDIR     = ../../bin/plug
CONFIG      += no_plugin_prefix

SOURCES += \
        xl_to_json_converter_loader_v1.cpp \
    get_template_by_name.cpp \
    xl_to_json_converter_thread_v1.cpp \
    xl_to_json_converter_task_v1.cpp \
    xl_to_json_converter_v1.cpp

HEADERS += \
        xl_to_json_converter_loader_v1.h \
    get_template_by_name.h \
    xl_to_json_converter_thread_v1.h \
    xl_to_json_converter_task_v1.h \
    xl_to_json_converter_v1.h

DISTFILES += xlToJsonConverterV1.json

LIBS += -lOle32

include(../pri/xlToJsonConverter.pri)
include(../pri/xlReader.pri)
include(../pri/factory.pri)
