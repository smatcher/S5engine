#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include <string>

#include <components/forwards.h>
#include <scenegraph/forwards.h>

namespace S5
{
    class IComponent
    {
    public:
        IComponent(SceneNodeWPtr node);
        virtual ~IComponent();

        SceneNodeWPtr node();
        void attachToNode(SceneNodeWPtr node);

        virtual std::string name() const = 0;
        virtual void update(double elapsed_time);

    private:
        struct Pimpl;
        std::unique_ptr<Pimpl> _p;
    };
}

#endif // ICOMPONENT_H
