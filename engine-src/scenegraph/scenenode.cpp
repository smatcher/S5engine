#include "scenenode.h"

#include <algorithm>

namespace S5
{

    struct SceneNode::Pimpl
    {
        std::string name;
        SceneNodeWPtr parent;

        SceneNodes children;
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

    const SceneNodes& SceneNode::children() const
    {
        return _p->children;
    }

    void SceneNode::reparentNode(SceneNodePtr parent, SceneNodePtr child)
    {
        SceneNodes& children = parent->_p->children;
        if (std::find(children.begin(), children.end(), child) == children.end())
        {
            if (child->parent() != 0)
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

        SceneNodes& vec = _p->children;
        vec.erase(std::remove(vec.begin(), vec.end(), child), vec.end());
    }
}
