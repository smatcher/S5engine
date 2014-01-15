#ifndef SCENENODE_H
#define SCENENODE_H

#include <string>
#include <vector>
#include <memory>

namespace S5
{
    class SceneNode;

    typedef std::shared_ptr<SceneNode> SceneNodePtr;
    typedef std::weak_ptr<SceneNode> SceneNodeWPtr;
    typedef std::vector<SceneNodePtr> SceneNodes;

    class SceneNode
    {
    public:
        SceneNode(std::string name, SceneNodePtr parent = 0);
        ~SceneNode();

        std::string name() const;
        void setName(const std::string& name);

        SceneNodePtr parent() const;
        const SceneNodes& children() const;

        void removeChild(SceneNodePtr child);

        static void reparentNode(SceneNodePtr parent, SceneNodePtr child);

    private:
        struct Pimpl;
        std::unique_ptr<Pimpl> _p;
    };
}

#endif // SCENENODE_H
