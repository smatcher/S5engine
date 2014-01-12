#ifndef ENGINE_H
#define ENGINE_H

#include <memory>

namespace S5
{
    class SceneGraph;

    class Engine
    {
    public:
        Engine();
        ~Engine();

        void init();

        void setCurrentScene(std::shared_ptr<SceneGraph> scene);
        std::shared_ptr<SceneGraph> currentScene();

    private:
        struct Pimpl;
        Pimpl* _p;
    };
}

#endif // ENGINE_H
