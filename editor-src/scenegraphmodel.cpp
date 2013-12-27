#include "scenegraphmodel.h"

#include "scenegraph/scenegraph.h"
#include "scenegraph/scenenode.h"

#include <QEvent>

SceneGraphModel::SceneGraphModel(QObject* parent, S5::SceneGraph* source_data) :
    QAbstractItemModel(parent),
    source_data(source_data)
{
}

S5::SceneNode* SceneGraphModel::getNode(const QModelIndex &index) const
{
    if (index.isValid() && index.internalPointer() != source_data)
	{
        S5::SceneNode *item = static_cast<S5::SceneNode*>(index.internalPointer());
		if (item) return item;
	}
	return 0;
}

QModelIndex SceneGraphModel::index(int row, int column, const QModelIndex& parent) const
{
	if (parent.isValid() && parent.column() != 0)
		return QModelIndex();

    S5::SceneNode *parentItem = getNode(parent);

	if(parentItem != 0)
	{
        S5::SceneNode *childItem = parentItem->children()[row];
		if (childItem)
			return createIndex(row, column, childItem);
		else
			return QModelIndex();
	}
	else
	{
        S5::SceneNode *childItem = source_data->rootNodes()[row];
		if (childItem)
			return createIndex(row, column, childItem);
		else
			return QModelIndex();
	}
}

QModelIndex SceneGraphModel::parent(const QModelIndex& index) const
{
	if (!index.isValid())
		return QModelIndex();

    S5::SceneNode *childItem = getNode(index);
    S5::SceneNode *parentItem = childItem->parent();

    if (parentItem == NULL)
		return QModelIndex();


    return createIndex(parentItem->children().size(), 0, parentItem);
}

int SceneGraphModel::rowCount(const QModelIndex& parent) const
{
    S5::SceneNode *parentItem = getNode(parent);

    if(parentItem != NULL)
        return parentItem->children().size();
	else
        return source_data->rootNodes().size();
}

int SceneGraphModel::columnCount(const QModelIndex&) const
{
	return 1;
}

QVariant SceneGraphModel::data(const QModelIndex& parent, int role) const
{
    if(role == Qt::DisplayRole || role == Qt::EditRole)
	{
        S5::SceneNode* n = getNode(parent);
        if(n != 0) return QVariant(QString::fromStdString(n->name()));
	}
	return QVariant();
}

bool SceneGraphModel::setData(const QModelIndex & parent, const QVariant & value, int role)
{
    if(role == Qt::EditRole)
    {
        S5::SceneNode* n = getNode(parent);
        if(n != 0)
        {
            n->setName(value.toString().toStdString());
            return true;
        }
    }
    return false;
}

Qt::ItemFlags SceneGraphModel::flags(const QModelIndex & index) const
{
    S5::SceneNode* n = getNode(index);
    if(n!=0)
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;

    return QAbstractItemModel::flags(index);
}

/*
bool SceneGraphModel::event(QEvent* evt)
{
	if(evt->type() == UPDATED_EVENT::type())
	{
		//emit dataChanged(QModelIndex(), QModelIndex());
		emit layoutChanged();
		return true;
	}
	else
	{
		return QAbstractItemModel::event(evt);
	}
}
*/
