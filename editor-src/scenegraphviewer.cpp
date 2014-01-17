#include "scenegraphviewer.h"
#include "ui_scenegraphviewer.h"
#include "scenegraphmodel.h"

#include <QMenu>
#include <QDebug>

SceneGraphViewer::SceneGraphViewer(QWidget *parent/*, QAbstractItemModel* model*/) :
    QWidget(parent),
    ui(new Ui::SceneGraphViewer)
{
    ui->setupUi(this);

    //ui->treeView->setModel(model);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->treeView, &QWidget::customContextMenuRequested, this, &SceneGraphViewer::showContextMenu);
}

SceneGraphViewer::~SceneGraphViewer()
{
    delete ui;
}

void SceneGraphViewer::sceneGraphChanged(std::shared_ptr<S5::SceneGraph> scenegraph)
{
    model.reset(new SceneGraphModel(nullptr, scenegraph));
    ui->treeView->setModel(model.get());
}

void SceneGraphViewer::showContextMenu(const QPoint& pos)
{
    if (!model)
        return;

    QModelIndex item = ui->treeView->indexAt(pos);

    QList<QAction*> actions;

    if (item.isValid())
    {
        actions << ui->actionAdd_Node;
        actions << ui->actionDelete_Node;
    }
    else
    {
        actions << ui->actionAdd_Node_At_Root;
    }
    if (actions.count() > 0)
    {
        QMenu::exec(actions, ui->treeView->mapToGlobal(pos));
    }
}

void SceneGraphViewer::on_actionAdd_Node_triggered()
{
    addNodeAtIndex(ui->treeView->currentIndex());
    ui->treeView->expand(ui->treeView->currentIndex());
}

void SceneGraphViewer::on_actionAdd_Node_At_Root_triggered()
{
    addNodeAtIndex(ui->treeView->rootIndex());
}

void SceneGraphViewer::on_actionDelete_Node_triggered()
{
    QModelIndex currentItem = ui->treeView->currentIndex();

    if (currentItem.isValid())
    {
        int row = currentItem.row();
        ui->treeView->model()->removeRow(row, currentItem.parent());
    }
}

void SceneGraphViewer::addNodeAtIndex(QModelIndex index)
{
    QAbstractItemModel* model = ui->treeView->model();
    int row = model->rowCount(index);
    ui->treeView->model()->insertRow(row, index);
}

