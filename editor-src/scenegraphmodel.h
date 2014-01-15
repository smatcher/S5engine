#ifndef SCENEGRAPHMODEL_H
#define SCENEGRAPHMODEL_H

#include <QAbstractItemModel>
#include <memory>

#include <scenegraph/scenegraph.h>
#include <scenegraph/scenenode.h>

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
    Qt::DropActions supportedDropActions() const;

    S5::SceneNodePtr getNode(const QModelIndex &index) const;
    S5::SceneNodePtr getNode(quintptr index) const;
    bool findIndex(S5::SceneNodeWPtr node, quintptr& index) const;

    QModelIndex customMakeIndex(int row, int column, S5::SceneNodeWPtr node) const;

    QStringList mimeTypes() const;
    QMimeData* mimeData(const QModelIndexList& indexes) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

    bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
    bool moveRows(const QModelIndex & sourceParent, int sourceRow, int count, const QModelIndex & destinationParent, int destinationChild);

signals:
    
public slots:

private:
    std::shared_ptr<S5::SceneGraph> source_data;
    mutable std::map<quintptr, S5::SceneNodeWPtr> index_map;
    mutable quintptr index_counter;
};

#endif // SCENEGRAPHMODEL_H
