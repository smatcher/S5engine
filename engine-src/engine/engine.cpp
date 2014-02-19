#include "engine.h"

#include <scenegraph/scenegraph.h>
#include <abstraction/irendercontext.h>
#include <abstraction/irenderviewport.h>
#include <ird/interface/irenderdevice.h>

#include <assert.h>

#include <GL/gl.h>

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
        _p = std::unique_ptr<Pimpl>(new Pimpl());
    }

    Engine::~Engine()
    {}

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
        static int progress = 0;
        progress = (progress + 30) % 1000;

        assert(isReadyToRender());

        float red = float(progress%1000) / 1000.0f;
        float green = float((progress+333)%1000) / 1000.0f;
        float blue = float((progress+666)%1000) / 1000.0f;

        glClearColor(0.0, 0.0, 0.0, 0.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
            glColor3f(red, 0.0, 0.0);
            glVertex3f(0.25, 0.75, 0.0);
            glColor3f(0.0, green, 0.0);
            glVertex3f(0.5, 0.25, 0.0);
            glColor3f(0.0, 0.0, blue);
            glVertex3f(0.75, 0.75, 0.0);
        glEnd();
        glFlush();
    }

}
