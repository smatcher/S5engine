#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace S5 {
class Engine;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(S5::Engine* engine, QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    S5::Engine* engine;
};

#endif // MAINWINDOW_H
