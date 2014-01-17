#ifndef SCENEGRAPHVIEWER_H
#define SCENEGRAPHVIEWER_H

#include <QWidget>
#include <QAbstractItemModel>
#include <memory>

namespace Ui {
class SceneGraphViewer;
}

namespace S5 {
class SceneGraph;
}

class SceneGraphViewer : public QWidget
{
    Q_OBJECT
    
public:
    explicit SceneGraphViewer(QWidget *parent = nullptr/*, QAbstractItemModel* model*/);
    ~SceneGraphViewer();
    
public slots:
    void sceneGraphChanged(std::shared_ptr<S5::SceneGraph> scenegraph);

private slots:
    void showContextMenu(const QPoint& pos);

    void on_actionAdd_Node_triggered();
    void on_actionAdd_Node_At_Root_triggered();
    void on_actionDelete_Node_triggered();

private:
    void addNodeAtIndex(QModelIndex index);

    Ui::SceneGraphViewer *ui;
    std::unique_ptr<QAbstractItemModel> model;
};

#endif // SCENEGRAPHVIEWER_H
