#-------------------------------------------------
#
# Project created by QtCreator 2014-11-15T20:17:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

SOURCES += main.cpp \
    MainWindow.cpp \
    FirstWindow.cpp \
    Cars.cpp \
    Driver.cpp \
    tree.cpp \
    EditCarWindow.cpp \
    undoStack.cpp \
    AddWindow.cpp

HEADERS  += \
    MainWindow.h \
    FirstWindow.h \
    Cars.h \
    Driver.h \
    tree.h \
    EditCarWindow.h \
    UndoStack.h \
    AddWindow.h

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x000000

FORMS    +=

RESOURCES += \
    Icons.qrc

OTHER_FILES +=
