#ifndef QGLRENDERCONTEXTADAPTER_H
#define QGLRENDERCONTEXTADAPTER_H

#include <abstraction/irendercontext.h>

#include <QGLContext>

class QGlRenderContextAdapter : public S5::IRenderContext
{
public:
    QGlRenderContextAdapter(QGLContext* context);
    virtual ~QGlRenderContextAdapter();

    virtual void makeCurrent();
    virtual std::unique_ptr<S5::IRD::IRenderDevice> createRenderDevice();

private:
    QGLContext* _context;
};

#endif // QGLRENDERCONTEXTADAPTER_H
