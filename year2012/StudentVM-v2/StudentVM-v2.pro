TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.c \
    commands.c \
    function.c \
    stack_memory.c \
    _interpreter.c \
    _parser.c \
    labels.c \
    _identification.c \
    errors.c

HEADERS += \
    vm_lib.h \
    stack_memory.h \
    cmd_lbl.h \
    errors.h

OTHER_FILES += \
    test1.svm \
    gcd.svm \
    error.svm \
    er_lbl.svm \
    er_int.svm \
    test1.svm \
    tests/test7.svm \
    tests/test6.svm \
    tests/test5.svm \
    tests/test4.svm \
    tests/test3.svm \
    tests/test2.svm \
    tests/test1.svm \
    fibonachi.svm \
    tasks/gcd.svm \
    tasks/fibonachi.svm \
    tasks/prime10001.svm \
    tasks/gpd.svm \
    tests/test8_bin.svm

