#ifndef ENGINE_H
#define ENGINE_H

#include <memory>

namespace S5
{
    class SceneGraph;
    class IRenderContext;
    class IRenderViewport;

    class Engine
    {
    public:
        Engine();
        ~Engine();

        void init();

        void setCurrentScene(std::shared_ptr<SceneGraph> scene);
        std::shared_ptr<SceneGraph> currentScene();

        void setupRenderer(std::shared_ptr<S5::IRenderContext> render_context, std::shared_ptr<S5::IRenderViewport> render_viewport);
        bool isReadyToRender();
        void renderStuff();

    private:
        struct Pimpl;
        Pimpl* _p;
    };
}

#endif // ENGINE_H
