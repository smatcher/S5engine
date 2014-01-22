#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

namespace S5 {
    class Engine;
}

class GLWidget : public QGLWidget
{
public:
    GLWidget(QWidget* parent);

    void setEngine(S5::Engine* engine);
    virtual void paintGL();

private:
    S5::Engine* engine;
};

#endif // GLWIDGET_H
