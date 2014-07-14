#include "consolewidget.h"
#include "ui_consolewidget.h"

ConsoleWidget::ConsoleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConsoleWidget)
{
    ui->setupUi(this);

    _output_model = new QStringListModel(this);
    ui->consoleOutput->setModel(_output_model);

    connect(ui->consoleInput, &QLineEdit::returnPressed, this, &ConsoleWidget::_processInput);
}

ConsoleWidget::~ConsoleWidget()
{
    delete ui;
}

void ConsoleWidget::setScriptInterpreter(S5::IScriptInterpreter* script_interpreter)
{
    _script_interpreter = script_interpreter;
}

void ConsoleWidget::_processInput()
{
  QString input = ui->consoleInput->text();
  ui->consoleInput->clear();

  if (_script_interpreter != nullptr)
     _script_interpreter->eval(input.toStdString());

  int insert_where = _output_model->rowCount();
  _output_model->insertRow(insert_where);
  QModelIndex new_index = _output_model->index(insert_where);
  _output_model->setData(new_index, ">>> " + input);
}
