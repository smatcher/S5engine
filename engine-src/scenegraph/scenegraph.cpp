#include "scenegraph.h"

#include "scenenode.h"

#include <algorithm>
#include <list>
#include <iostream>

namespace S5
{
    struct SceneGraph::Pimpl
    {
        SceneNodePtr root_node;
    };

    SceneGraph::SceneGraph()
    {
        _p = std::unique_ptr<Pimpl>(new Pimpl());

        _p->root_node = std::make_shared<SceneNode>("Root");
    }

    SceneGraph::~SceneGraph()
    {}

    SceneNodePtr SceneGraph::rootNode()
    {
        return _p->root_node;
    }

    const SceneNodePtr SceneGraph::rootNode() const
    {
        return _p->root_node;
    }

    void SceneGraph::DEBUG_PRINT() const
    {
        typedef std::pair<int, SceneNode*> Pair;
        std::list<Pair> stack;
        stack.push_back(Pair(0, _p->root_node.get()));

        while(! stack.empty())
        {
            Pair p = stack.back();
            stack.pop_back();

            for (auto it = p.second->children().rbegin() ; it != p.second->children().rend() ; ++it)
                stack.push_back(Pair(p.first+1, it->get()));

            std::cout << "(" << p.first << ")" << p.second->name() << " [" << p.second << ":" << p.second->parent() << "]" << std::endl;
        }
    }
}
