#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <scenegraph/forwards.h>

namespace S5
{
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
