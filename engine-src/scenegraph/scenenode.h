#ifndef SCENENODE_H
#define SCENENODE_H

#include <string>
#include <vector>

namespace S5
{
    class SceneNode;
    typedef std::vector<SceneNode*> SceneNodes;

    class SceneNode
    {
    public:
        SceneNode(std::string name, SceneNode* parent = NULL);
        ~SceneNode();

        std::string name() const;
        void setName(const std::string& name);

        SceneNode* parent() const;
        const SceneNodes& children() const;

        void addChild(SceneNode* child);
        void removeChild(SceneNode* child);

    private:
        struct Pimpl;
        Pimpl* _p;
    };
}

#endif // SCENENODE_H
