#include "scenenode.h"

#include <algorithm>

namespace S5
{

    struct SceneNode::Pimpl
    {
        std::string name;
        SceneNode* parent;

        SceneNodes children;
    };

    SceneNode::SceneNode(std::string name, SceneNode* parent)
    {
        _p = new Pimpl();

        _p->name = name;
        _p->parent = parent;
    }

    SceneNode::~SceneNode()
    {
        delete _p;
    }

    std::string SceneNode::name() const
    {
        return _p->name;
    }

    void SceneNode::setName(const std::string& name)
    {
        _p->name = name;
    }

    SceneNode* SceneNode::parent() const
    {
        return _p->parent;
    }

    const SceneNodes& SceneNode::children() const
    {
        return _p->children;
    }

    void SceneNode::addChild(SceneNode* child)
    {
        if (std::find(_p->children.begin(), _p->children.end(), child) == _p->children.end())
        {
            if (child->parent() != 0)
            {
                child->parent()->removeChild(child);
            }

            _p->children.push_back(child);
            child->_p->parent = this;
        }
    }

    void SceneNode::removeChild(SceneNode* child)
    {
        child->_p->parent = 0;

        SceneNodes& vec = _p->children;
        vec.erase(std::remove(vec.begin(), vec.end(), child), vec.end());
    }
}
