#ifndef SCENEGRAPH_FORWARDS_H
#define SCENEGRAPH_FORWARDS_H

#include <memory>
#include <vector>

namespace S5
{
    class SceneGraph;
    typedef std::shared_ptr<SceneGraph> SceneGraphPtr;

    class SceneNode;
    typedef std::shared_ptr<SceneNode> SceneNodePtr;
    typedef std::weak_ptr<SceneNode> SceneNodeWPtr;
    typedef std::vector<SceneNodePtr> SceneNodeSet;
}

#endif // SCENEGRAPH_FORWARDS_H
