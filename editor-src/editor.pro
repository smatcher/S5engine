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
    scenegraphmodel.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    scenegraphviewer.h \
    scenegraphmodel.h

FORMS    += mainwindow.ui \
    scenegraphviewer.ui

CONFIG(debug,debug|release) {
	ENGINE_BIN = $$PWD/../engine-bin-debug/
}
CONFIG(release,debug|release) {
	ENGINE_BIN = $$PWD/../engine-bin-release/
}

unix:!macx:!symbian: LIBS += -L$$ENGINE_BIN -lengine

INCLUDEPATH += $$PWD/../engine-src
DEPENDPATH += $$PWD/../engine-src

unix:!macx:!symbian: PRE_TARGETDEPS += $$ENGINE_BIN/libengine.a
