TEMPLATE = subdirs

SUBDIRS += \
    external \
    app \
    lib \
    others

lib.depends = external
app.depends = lib
