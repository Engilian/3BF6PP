QT       += core gui axcontainer

TARGET      = xlAxReader
TEMPLATE    = lib
CONFIG      += plugin
CONFIG      += c++11
DESTDIR     = ../../bin/plug
CONFIG      += no_plugin_prefix


SOURCES += \
        xl_ax_reader_loader.cpp \
    xl_ax_table.cpp \
    xl_ax_reader.cpp

HEADERS += \
        xl_ax_reader_loader.h \
    xl_ax_table.h \
    xl_ax_reader.h

DISTFILES += xlAxReader.json 

include(../pri/xlReader.pri)
include(../pri/factory.pri)
