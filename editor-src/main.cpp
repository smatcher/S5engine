#include <QApplication>
#include "mainwindow.h"

#include <engine/engine.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    S5::Engine engine;
    engine.init();

    MainWindow w(&engine);
    w.show();
    
    return a.exec();
}
