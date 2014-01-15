#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <vector>

namespace S5
{
    class SceneNode;

    class SceneGraph
    {
    public:
        SceneGraph();
        ~SceneGraph();

        const std::vector<SceneNode*>& rootNodes() const;
        void addRootNode(SceneNode* node);
        void removeRootNode(SceneNode* node);

        void DEBUG_PRINT() const;
    private:
        struct Pimpl;
        Pimpl* _p;
    };
}

#endif // SCENEGRAPH_H
