TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        lib/error_functions.c \
        lib/fileio/copy.c \
        lib/fileio/read_from_anywhere.c \
        lib/get_num.c \
        main.c

HEADERS += \
    lib/ename.c.inc \
    lib/error_functions.h \
    lib/get_num.h \
    lib/tlpi_hdr.h
