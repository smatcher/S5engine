#include "scenegraphviewer.h"
#include "ui_scenegraphviewer.h"

SceneGraphViewer::SceneGraphViewer(QWidget *parent, QAbstractItemModel* model) :
    QDockWidget(parent),
    ui(new Ui::SceneGraphViewer)
{
    ui->setupUi(this);

    ui->treeView->setModel(model);
}

SceneGraphViewer::~SceneGraphViewer()
{
    delete ui;
}
