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

    std::string SceneNode::name()
    {
        return _p->name;
    }

    void SceneNode::setName(const std::string& name)
    {
        _p->name = name;
    }

    SceneNode* SceneNode::parent()
    {
        return _p->parent;
    }

    SceneNodes SceneNode::children()
    {
        return _p->children;
    }

    void SceneNode::addChild(SceneNode* child)
    {
        if (std::find(_p->children.begin(), _p->children.end(), child) == _p->children.end())
        {
            if (child->parent() != NULL)
            {
                child->parent()->removeChild(child);
            }

            _p->children.push_back(child);
            child->_p->parent = this;
        }
    }

    void SceneNode::removeChild(SceneNode* child)
    {
        child->_p->parent = NULL;
        std::remove(_p->children.begin(), _p->children.end(), child);
    }
}
