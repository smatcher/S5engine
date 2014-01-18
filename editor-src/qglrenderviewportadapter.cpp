#include "qglrenderviewportadapter.h"

QGlRenderViewportAdapter::QGlRenderViewportAdapter(GLWidget* gl_widget)
    : IRenderViewport()
    , _gl_widget(gl_widget)
{}

QGlRenderViewportAdapter::~QGlRenderViewportAdapter()
{}


int QGlRenderViewportAdapter::width()
{
    return _gl_widget->width();
}

int QGlRenderViewportAdapter::height()
{
    return _gl_widget->height();
}

