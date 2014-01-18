#ifndef IRENDERVIEWPORT_H
#define IRENDERVIEWPORT_H

namespace S5
{
    class IRenderViewport
    {
    public:
        IRenderViewport() {}
        virtual ~IRenderViewport() {}

        virtual int width() = 0;
        virtual int height() = 0;
    };
}

#endif // IRENDERVIEWPORT_H
