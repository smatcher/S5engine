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
    
private slots:
    void showContextMenu(const QPoint& pos);

    void on_actionAdd_Node_triggered();
    void on_actionAdd_Node_At_Root_triggered();
    void on_actionDelete_Node_triggered();

private:
    void addNodeAtIndex(QModelIndex index);

    Ui::SceneGraphViewer *ui;
};

#endif // SCENEGRAPHVIEWER_H
