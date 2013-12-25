#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "glwidget.h"
#include "scenegraphviewer.h"
#include "scenegraphmodel.h"

#include "scenegraph/scenegraph.h"
#include "scenegraph/scenenode.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->centralWidget = new GLWidget(this);
    setCentralWidget(ui->centralWidget);

    S5::SceneGraph* scenegraph = new S5::SceneGraph();
    S5::SceneNode* n1 = new S5::SceneNode("toto_n1");
    scenegraph->addRootNode(n1);
    S5::SceneNode* n2 = new S5::SceneNode("toto_n2");
    scenegraph->addRootNode(n2);
    S5::SceneNode* n2_1 = new S5::SceneNode("tata_n2_1");
    n2->addChild(n2_1);
    S5::SceneNode* n2_2 = new S5::SceneNode("tata_n2_2");
    n2->addChild(n2_2);
    S5::SceneNode* n2_3 = new S5::SceneNode("tata_n2_3");
    n2->addChild(n2_3);
    S5::SceneNode* n3 = new S5::SceneNode("toto_n3");
    scenegraph->addRootNode(n3);


    SceneGraphModel* scenegraph_model = new SceneGraphModel(this, scenegraph);
    SceneGraphViewer* scenegraph_viewer = new SceneGraphViewer(this, scenegraph_model);
    addDockWidget(Qt::LeftDockWidgetArea, scenegraph_viewer);
}

MainWindow::~MainWindow()
{
    delete ui;
}
