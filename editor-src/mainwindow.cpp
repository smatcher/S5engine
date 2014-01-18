#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "glwidget.h"
#include "scenegraphviewer.h"
#include "scenegraphmodel.h"
#include "qglrendercontextadapter.h"
#include "qglrenderviewportadapter.h"

#include <engine/engine.h>

#include <scenegraph/scenegraph.h>
#include <scenegraph/scenenode.h>

MainWindow::MainWindow(S5::Engine* engine, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    engine(engine)
{
    ui->setupUi(this);

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

    ui->sceneGraphViewer->sceneGraphChanged(scenegraph);

    render_context = std::shared_ptr<S5::IRenderContext>(new QGlRenderContextAdapter(ui->renderViewport->context()));
    render_viewport = std::shared_ptr<S5::IRenderViewport>(new QGlRenderViewportAdapter(ui->renderViewport));
    engine->setupRenderer(render_context, render_viewport);
}

MainWindow::~MainWindow()
{
    delete ui;
}
