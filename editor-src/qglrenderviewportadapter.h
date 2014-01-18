#ifndef QGLRENDERVIEWPORTADAPTER_H
#define QGLRENDERVIEWPORTADAPTER_H

#include <abstraction/irenderviewport.h>

#include "glwidget.h"

class QGlRenderViewportAdapter : public S5::IRenderViewport
{
public:
    QGlRenderViewportAdapter(GLWidget* gl_widget);
    virtual ~QGlRenderViewportAdapter();

    virtual int width();
    virtual int height();

private:
    GLWidget* _gl_widget;
};

#endif // QGLRENDERVIEWPORTADAPTER_H
