#include "icomponent.h"

namespace S5
{

    struct IComponent::Pimpl
    {
        SceneNodeWPtr node;
    };

    IComponent::IComponent(SceneNodeWPtr node)
    {
        _p = std::unique_ptr<Pimpl>(new Pimpl());

        attachToNode(node);
    }

    IComponent::~IComponent()
    {}

    SceneNodeWPtr IComponent::node()
    {
        return _p->node;
    }

    void IComponent::attachToNode(SceneNodeWPtr node)
    {
        if (node.lock() == _p->node.lock())
            return;

        // TODO: notify old node
        _p->node = node;
        // TODO: notify new node
    }

    void IComponent::update(double)
    {}
}
