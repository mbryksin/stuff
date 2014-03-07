TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    printer.cpp \
    printertofile.cpp \
    printertoconsole.cpp

HEADERS += \
    printer.h \
    printertofile.h \
    printertoconsole.h

OTHER_FILES += \
    out.txt \
    in.txt

