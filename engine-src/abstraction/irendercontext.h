#ifndef IRENDERCONTEXT_H
#define IRENDERCONTEXT_H

#include <ird/interface/irenderdevice.h>

#include <memory>

namespace S5
{
    class IRenderContext
    {
    public:
        IRenderContext() {}
        virtual ~IRenderContext() {}

        virtual void makeCurrent() = 0;
        virtual std::unique_ptr<IRD::IRenderDevice> createRenderDevice() = 0;
    };
}

#endif // IRENDERCONTEXT_H
