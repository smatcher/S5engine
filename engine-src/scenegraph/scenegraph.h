#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <vector>
#include <memory>

namespace S5
{
    class SceneNode;
    typedef std::shared_ptr<SceneNode> SceneNodePtr;

    class SceneGraph
    {
    public:
        SceneGraph();
        ~SceneGraph();

        SceneNodePtr rootNode();
        const SceneNodePtr rootNode() const;

        void DEBUG_PRINT() const;
    private:
        struct Pimpl;
        std::unique_ptr<Pimpl> _p;
    };
}

#endif // SCENEGRAPH_H
