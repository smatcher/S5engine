#include "qglrendercontextadapter.h"

#include <ird/opengl2/gl2renderdevice.h>

#include <assert.h>

QGlRenderContextAdapter::QGlRenderContextAdapter(QGLContext* context)
    : S5::IRenderContext()
    , _context(context)
{
    assert(_context != 0);
}

QGlRenderContextAdapter::~QGlRenderContextAdapter()
{
}

void QGlRenderContextAdapter::makeCurrent()
{
    _context->makeCurrent();
}

std::unique_ptr<S5::IRD::IRenderDevice> QGlRenderContextAdapter::createRenderDevice()
{
    return std::unique_ptr<S5::IRD::IRenderDevice>(new S5::IRD::GL2RenderDevice());
}
