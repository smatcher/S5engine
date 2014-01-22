#include "scenenode.h"

#include <algorithm>

#include <components/icomponent.h>

namespace S5
{

    struct SceneNode::Pimpl
    {
        std::string name;
        SceneNodeWPtr parent;

        SceneNodeSet children;
        ComponentSet components;
    };

    SceneNode::SceneNode(std::string name, SceneNodePtr parent)
    {
        _p = std::unique_ptr<Pimpl>(new Pimpl());

        _p->name = name;
        _p->parent = parent;
    }

    SceneNode::~SceneNode()
    {}

    std::string SceneNode::name() const
    {
        return _p->name;
    }

    void SceneNode::setName(const std::string& name)
    {
        _p->name = name;
    }

    SceneNodePtr SceneNode::parent() const
    {
        return _p->parent.lock();
    }

    const SceneNodeSet& SceneNode::children() const
    {
        return _p->children;
    }

    void SceneNode::reparentNode(SceneNodePtr parent, SceneNodePtr child)
    {
        SceneNodeSet& children = parent->_p->children;
        if (std::find(children.begin(), children.end(), child) == children.end())
        {
            if (child->parent() != nullptr)
            {
                child->parent()->removeChild(child);
            }

            children.push_back(child);
            child->_p->parent = parent;
        }
    }

    void SceneNode::removeChild(SceneNodePtr child)
    {
        child->_p->parent.reset();

        SceneNodeSet& vec = _p->children;
        vec.erase(std::remove(vec.begin(), vec.end(), child), vec.end());
    }
}
