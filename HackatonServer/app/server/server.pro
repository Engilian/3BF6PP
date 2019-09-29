QT          += core gui widgets network

TARGET      = server
TEMPLATE    = app
CONFIG      += c++11
DESTDIR     = ../../bin

SOURCES += \
        main.cpp \
        server_mw.cpp \
    tasks_widget.cpp \
    task_process_widget.cpp \
    table_list_widget.cpp \
    server_http_request_handler.cpp

HEADERS += \
        server_mw.h \
    tasks_widget.h \
    task_process_widget.h \
    table_list_widget.h \
    server_http_request_handler.h

FORMS += \
        server_mw.ui \
    tasks_widget.ui \
    task_process_widget.ui \
    table_list_widget.ui


include(xlReader.pri)
include(httpServer.pri)
include(xlToJsonConverter.pri)
include(factory.pri)
