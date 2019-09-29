QT          -= gui

TARGET      = xlReader
TEMPLATE    = lib
CONFIG      += staticlib
CONFIG      += c++11

SOURCES += \
        xl_reader.cpp \
    xl_table.cpp

HEADERS += \
        xl_reader.h \
    xl_table.h
