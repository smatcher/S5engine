#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "glwidget.h"
#include "scenegraphviewer.h"
#include "scenegraphmodel.h"

#include <engine/engine.h>

#include <scenegraph/scenegraph.h>
#include <scenegraph/scenenode.h>

MainWindow::MainWindow(S5::Engine* engine, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    engine(engine)
{
    ui->setupUi(this);

    ui->centralWidget = new GLWidget(this);
    setCentralWidget(ui->centralWidget);

    std::shared_ptr<S5::SceneGraph> scenegraph = engine->currentScene();

    S5::SceneNodePtr root = scenegraph->rootNode();
    S5::SceneNodePtr n1 = std::make_shared<S5::SceneNode>("toto_n1");
    S5::SceneNodePtr n2 = std::make_shared<S5::SceneNode>("toto_n2");
    S5::SceneNodePtr n2_1 = std::make_shared<S5::SceneNode>("tata_n2_1");
    S5::SceneNodePtr n2_2 = std::make_shared<S5::SceneNode>("tata_n2_2");
    S5::SceneNodePtr n2_3 = std::make_shared<S5::SceneNode>("tata_n2_3");
    S5::SceneNodePtr n3 = std::make_shared<S5::SceneNode>("toto_n3");

    S5::SceneNode::reparentNode(root, n1);
    S5::SceneNode::reparentNode(root, n2);
    S5::SceneNode::reparentNode(n2, n2_1);
    S5::SceneNode::reparentNode(n2, n2_2);
    S5::SceneNode::reparentNode(n2, n2_3);
    S5::SceneNode::reparentNode(root, n3);

    SceneGraphModel* scenegraph_model = new SceneGraphModel(this, scenegraph);
    SceneGraphViewer* scenegraph_viewer = new SceneGraphViewer(this, scenegraph_model);
    addDockWidget(Qt::LeftDockWidgetArea, scenegraph_viewer);
}

MainWindow::~MainWindow()
{
    delete ui;
}
