#-------------------------------------------------
#
# Project created by QtCreator 2013-12-22T16:30:45
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = editor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    scenegraphviewer.cpp \
    scenegraphmodel.cpp \
    consolewidget.cpp \
    qglrendercontextadapter.cpp \
    qglrenderviewportadapter.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    scenegraphviewer.h \
    scenegraphmodel.h \
    consolewidget.h \
    qglrendercontextadapter.h \
    qglrenderviewportadapter.h

FORMS    += mainwindow.ui \
    scenegraphviewer.ui \
    consolewidget.ui

CONFIG(debug,debug|release) {
	ENGINE_BIN = $$PWD/../engine-bin-debug/
}
CONFIG(release,debug|release) {
	ENGINE_BIN = $$PWD/../engine-bin-release/
}

CONFIG += c++11

LIBS += -llua -ldl
LIBS += -L$$ENGINE_BIN -lengine

INCLUDEPATH += $$PWD/../engine-src
DEPENDPATH += $$PWD/../engine-src

win32 {
    PRE_TARGETDEPS += $$ENGINE_BIN/libengine.a
}
!win32 {
    PRE_TARGETDEPS += $$ENGINE_BIN/libengine.so
}
