#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "glwidget.h"
#include "scenegraphviewer.h"
#include "scenegraphmodel.h"
#include "qglrendercontextadapter.h"
#include "qglrenderviewportadapter.h"
#include "qtimer.h"

#include <engine/engine.h>

#include <scenegraph/scenegraph.h>
#include <scenegraph/scenenode.h>

MainWindow::MainWindow(S5::Engine* engine, S5::IScriptInterpreter* script_interpreter, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    engine(engine),
    script_interpreter(script_interpreter)
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

    ui->renderViewport->setEngine(engine);
    ui->console->setScriptInterpreter(script_interpreter);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), ui->renderViewport, SLOT(updateGL()));
    timer->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}
