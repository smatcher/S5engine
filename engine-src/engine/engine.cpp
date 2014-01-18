#include "engine.h"

#include <scenegraph/scenegraph.h>
#include <abstraction/irendercontext.h>
#include <abstraction/irenderviewport.h>
#include <ird/interface/irenderdevice.h>

#include <assert.h>

namespace S5
{
    struct Engine::Pimpl
    {
        std::shared_ptr<SceneGraph> current_scene;
        std::shared_ptr<S5::IRenderContext> render_context;
        std::shared_ptr<S5::IRenderViewport> render_viewport;

        std::unique_ptr<S5::IRD::IRenderDevice> render_device;
    };

    Engine::Engine()
    {
        _p = new Pimpl();
    }

    Engine::~Engine()
    {
        delete _p;
    }

    void Engine::init()
    {
        _p->current_scene = std::make_shared<SceneGraph>();
    }

    void Engine::setCurrentScene(std::shared_ptr<SceneGraph> scene)
    {
        _p->current_scene = scene;
    }

    std::shared_ptr<SceneGraph> Engine::currentScene()
    {
        return _p->current_scene;
    }

    void Engine::setupRenderer(std::shared_ptr<S5::IRenderContext> render_context, std::shared_ptr<S5::IRenderViewport> render_viewport)
    {
        _p->render_context = render_context;
        _p->render_viewport = render_viewport;
        _p->render_device = render_context->createRenderDevice();
    }

    bool Engine::isReadyToRender()
    {
        return _p->current_scene && _p->render_context && _p->render_viewport;
    }

    void Engine::renderStuff()
    {
        assert(isReadyToRender());
    }

}
