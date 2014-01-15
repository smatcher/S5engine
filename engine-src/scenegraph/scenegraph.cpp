#include "scenegraph.h"

#include "scenenode.h"

#include <algorithm>
#include <list>
#include <iostream>

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

    const std::vector<SceneNode*>& SceneGraph::rootNodes() const
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
        SceneNodes& vec = _p->root_nodes;
        vec.erase(std::remove(vec.begin(), vec.end(), node), vec.end());
    }

    void SceneGraph::DEBUG_PRINT() const
    {
        typedef std::pair<int, SceneNode*> Pair;
        std::list<Pair> stack;
        for (auto it = rootNodes().rbegin() ; it != rootNodes().rend() ; ++it)
            stack.push_back(Pair(0, *it));

        while(! stack.empty())
        {
            Pair p = stack.back();
            stack.pop_back();

            for (auto it = p.second->children().rbegin() ; it != p.second->children().rend() ; ++it)
                stack.push_back(Pair(p.first+1, *it));

            std::cout << "(" << p.first << ")" << p.second->name() << " [" << p.second << ":" << p.second->parent() << "]" << std::endl;
        }
    }
}
