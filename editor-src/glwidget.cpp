#include "glwidget.h"

#include <engine/engine.h>

GLWidget::GLWidget(QWidget* parent)
    : QGLWidget(parent)
    , engine(nullptr)
{
}

void GLWidget::setEngine(S5::Engine* engine)
{
    this->engine = engine;
}

void GLWidget::paintGL()
{
    if (engine)
        engine->renderStuff();
}
