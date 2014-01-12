#include "engine.h"

#include <scenegraph/scenegraph.h>

namespace S5
{
    struct Engine::Pimpl
    {
        std::shared_ptr<SceneGraph> current_scene;
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
}
