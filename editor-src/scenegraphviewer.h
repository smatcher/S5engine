#ifndef SCENEGRAPHVIEWER_H
#define SCENEGRAPHVIEWER_H

#include <QDockWidget>
#include <QAbstractItemModel>

namespace Ui {
class SceneGraphViewer;
}

class SceneGraphViewer : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit SceneGraphViewer(QWidget *parent, QAbstractItemModel* model);
    ~SceneGraphViewer();
    
private:
    Ui::SceneGraphViewer *ui;
};

#endif // SCENEGRAPHVIEWER_H
