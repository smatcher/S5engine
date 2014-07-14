#include <QApplication>
#include "mainwindow.h"

#include <engine/engine.h>
#include <lua/luainterpreter.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    S5::Engine engine;
    engine.init();

    S5::LuaInterpreter lua_interpreter;
    lua_interpreter.init();

    MainWindow w(&engine, &lua_interpreter);
    w.show();
    
    return a.exec();
}
