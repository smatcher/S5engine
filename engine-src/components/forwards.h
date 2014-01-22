#ifndef COMPONENTS_FORWARDS_H
#define COMPONENTS_FORWARDS_H

#include <memory>
#include <vector>

namespace S5
{
    class IComponent;
    typedef std::unique_ptr<IComponent> ComponentPtr;
    typedef std::vector<ComponentPtr> ComponentSet;
}

#endif // COMPONENTS_FORWARDS_H
