#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QWidget>
#include <QStringListModel>

#include <abstraction/iscriptinterpreter.h>

namespace Ui {
class ConsoleWidget;
}

class ConsoleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConsoleWidget(QWidget *parent = nullptr);
    ~ConsoleWidget();

    void setScriptInterpreter(S5::IScriptInterpreter* script_interpreter);

private slots:
    void _processInput();

private:
    Ui::ConsoleWidget *ui;
    QStringListModel* _output_model;

    S5::IScriptInterpreter* _script_interpreter;

};

#endif // CONSOLEWIDGET_H
