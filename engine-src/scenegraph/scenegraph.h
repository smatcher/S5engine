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

        std::vector<SceneNode*> rootNodes();
        void addRootNode(SceneNode* node);
        void removeRootNode(SceneNode* node);

    private:
        struct Pimpl;
        Pimpl* _p;
    };
}

#endif // SCENEGRAPH_H
