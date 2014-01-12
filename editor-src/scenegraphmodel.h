#ifndef SCENEGRAPHMODEL_H
#define SCENEGRAPHMODEL_H

#include <QAbstractItemModel>
#include <memory>

namespace S5
{
    class SceneNode;
    class SceneGraph;
}

class SceneGraphModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit SceneGraphModel(QObject* parent, std::shared_ptr<S5::SceneGraph> source_data);
 
	QModelIndex index(int row, int column, const QModelIndex &parent) const;
	QModelIndex parent(const QModelIndex&) const;
	int rowCount(const QModelIndex&) const;
	int columnCount(const QModelIndex&) const;
	QVariant data(const QModelIndex&, int role) const;
    bool setData(const QModelIndex & parent, const QVariant & value, int role);
    Qt::ItemFlags flags(const QModelIndex & index) const;

    S5::SceneNode* getNode(const QModelIndex &index) const;
   
signals:
    
public slots:

private:
    std::shared_ptr<S5::SceneGraph> source_data;
};

#endif // SCENEGRAPHMODEL_H
