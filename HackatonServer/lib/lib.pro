TEMPLATE = subdirs

SUBDIRS += \
    xlReader \
    xlAxReader \
    xlToJsonConverter \
    xlToJsonConverterV1

xlAxReader.depends = xlReader
xlToJsonConverter.depends = xlReader
xlToJsonConverterV1.depends = xlToJsonConverter
