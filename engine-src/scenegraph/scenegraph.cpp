#include "scenegraph.h"

#include "scenenode.h"

#include <algorithm>

namespace S5
{
    struct SceneGraph::Pimpl
    {
        SceneNodes root_nodes;
    };

    SceneGraph::SceneGraph()
    {
        _p = new Pimpl();
    }

    SceneGraph::~SceneGraph()
    {
        delete _p;
    }

    std::vector<SceneNode*> SceneGraph::rootNodes()
    {
        return _p->root_nodes;
    }

    void SceneGraph::addRootNode(SceneNode* node)
    {
        if (std::find(_p->root_nodes.begin(), _p->root_nodes.end(), node) == _p->root_nodes.end())
        {
            if (node->parent() != NULL)
            {
                node->parent()->removeChild(node);
            }

            _p->root_nodes.push_back(node);
        }
    }

    void SceneGraph::removeRootNode(SceneNode* node)
    {
        std::remove(_p->root_nodes.begin(), _p->root_nodes.end(), node);
    }
}
