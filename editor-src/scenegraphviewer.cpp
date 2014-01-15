#include "scenegraphviewer.h"
#include "ui_scenegraphviewer.h"

#include <QMenu>
#include <QDebug>

SceneGraphViewer::SceneGraphViewer(QWidget *parent, QAbstractItemModel* model) :
    QDockWidget(parent),
    ui(new Ui::SceneGraphViewer)
{
    ui->setupUi(this);

    ui->treeView->setModel(model);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->treeView, &QWidget::customContextMenuRequested, this, &SceneGraphViewer::showContextMenu);
}

SceneGraphViewer::~SceneGraphViewer()
{
    delete ui;
}

void SceneGraphViewer::showContextMenu(const QPoint& pos)
{
    QModelIndex item = ui->treeView->indexAt(pos);

    QList<QAction*> actions;
    if (item.isValid())
    {
        actions << ui->actionAdd_Node;
        actions << ui->actionDelete_Node;
    }
    if (actions.count() > 0)
    {
        QMenu::exec(actions, ui->treeView->mapToGlobal(pos));
    }
}

void SceneGraphViewer::on_actionAdd_Node_triggered()
{
    QModelIndex selectedItem = ui->treeView->currentIndex();

    if (selectedItem.isValid())
    {
        QAbstractItemModel* model = ui->treeView->model();
        int row = model->rowCount(selectedItem);
        ui->treeView->model()->insertRow(row, selectedItem);
    }
}

void SceneGraphViewer::on_actionDelete_Node_triggered()
{
    QModelIndex selectedItem = ui->treeView->currentIndex();

    if (selectedItem.isValid())
    {
        int row = selectedItem.row();
        ui->treeView->model()->removeRow(row, selectedItem.parent());
    }
}
