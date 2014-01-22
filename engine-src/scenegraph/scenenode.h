#ifndef SCENENODE_H
#define SCENENODE_H

#include <string>

#include <scenegraph/forwards.h>
#include <components/forwards.h>

namespace S5
{
    class SceneNode
    {
    public:
        SceneNode(std::string name, SceneNodePtr parent = nullptr);
        ~SceneNode();

        std::string name() const;
        void setName(const std::string& name);

        SceneNodePtr parent() const;
        const SceneNodeSet& children() const;

        void removeChild(SceneNodePtr child);

        static void reparentNode(SceneNodePtr parent, SceneNodePtr child);

        void addComponent(ComponentPtr component);
        const ComponentSet& components() const;

    private:
        struct Pimpl;
        std::unique_ptr<Pimpl> _p;
    };
}

#endif // SCENENODE_H
