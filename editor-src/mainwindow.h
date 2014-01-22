#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

namespace Ui {
class MainWindow;
}

namespace S5 {
class Engine;
class IRenderContext;
class IRenderViewport;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(S5::Engine* engine, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    S5::Engine* engine;

    std::shared_ptr<S5::IRenderContext> render_context;
    std::shared_ptr<S5::IRenderViewport> render_viewport;
};

#endif // MAINWINDOW_H
