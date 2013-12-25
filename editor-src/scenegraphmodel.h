#ifndef SCENEGRAPHMODEL_H
#define SCENEGRAPHMODEL_H

#include <QAbstractItemModel>

namespace S5
{
    class SceneNode;
    class SceneGraph;
}

class SceneGraphModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit SceneGraphModel(QObject* parent, S5::SceneGraph* source_data);
 
	QModelIndex index(int row, int column, const QModelIndex &parent) const;
	QModelIndex parent(const QModelIndex&) const;
	int rowCount(const QModelIndex&) const;
	int columnCount(const QModelIndex&) const;
	QVariant data(const QModelIndex&, int role) const;
    //virtual bool event(QEvent* evt);

    S5::SceneNode* getNode(const QModelIndex &index) const;
   
signals:
    
public slots:

private:
    S5::SceneGraph* source_data;
};

#endif // SCENEGRAPHMODEL_H
