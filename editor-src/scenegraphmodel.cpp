#include "scenegraphmodel.h"

#include "scenegraph/scenegraph.h"
#include "scenegraph/scenenode.h"

#include <QEvent>
#include <QDebug>
#include <QStringList>
#include <QMimeData>

static const QString node_mime_type = "S5editor/SceneNodePtr";

SceneGraphModel::SceneGraphModel(QObject* parent, std::shared_ptr<S5::SceneGraph> source_data) :
    QAbstractItemModel(parent),
    source_data(source_data)
{
}

S5::SceneNode* SceneGraphModel::getNode(const QModelIndex &index) const
{
    if (index.isValid() && index.internalPointer() != source_data.get())
	{
        S5::SceneNode *item = static_cast<S5::SceneNode*>(index.internalPointer());
        if (item)
            return item;
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
    S5::SceneNode *childItem = getNode(index);

    if (childItem == 0)
        return QModelIndex();

    S5::SceneNode *parentItem = childItem->parent();

    if (parentItem == 0)
		return QModelIndex();

    return createIndex(parentItem->children().size(), 0, parentItem);
}

int SceneGraphModel::rowCount(const QModelIndex& parent) const
{
    S5::SceneNode *parentItem = getNode(parent);

    if(parentItem != 0)
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
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
    else
        return QAbstractItemModel::flags(index) | Qt::ItemIsDropEnabled;
}

Qt::DropActions SceneGraphModel::supportedDropActions() const
{
     return Qt::MoveAction;
}

QStringList SceneGraphModel::mimeTypes() const
{
    QStringList types;
    types << node_mime_type;
    return types;
}

QMimeData* SceneGraphModel::mimeData(const QModelIndexList& indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (const QModelIndex &index, indexes) {
        S5::SceneNode* node = getNode(index);
        if (node != 0) {
            stream << qintptr(node);
        }
    }

    mimeData->setData(node_mime_type, encodedData);
    return mimeData;
}

bool SceneGraphModel::dropMimeData(const QMimeData *data,
    Qt::DropAction action, int /*row*/, int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;

    if (!data->hasFormat(node_mime_type))
        return false;

    if (column > 0)
        return false;

    QByteArray encodedData = data->data(node_mime_type);
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QList<S5::SceneNode*> newItems;
    int rows = 0;

    while (!stream.atEnd()) {
        qintptr node;
        stream >> node;
        newItems << (S5::SceneNode*)node;
        ++rows;
    }

    S5::SceneNode* parent_node = getNode(parent);
    int row;

    if (parent_node != 0)
        row = parent_node->children().size();
    else
        row = source_data->rootNodes().size();

    int row_count = 0;
    foreach (S5::SceneNode* node, newItems) {
        if (node != 0)
            row_count++;
    }

    beginResetModel();
    //emit layoutAboutToBeChanged();
    qDebug() << "beginInsertRows" << row << row+row_count-1 << parent;
    //beginInsertRows(parent, row, row+row_count-1);
    foreach (S5::SceneNode* node, newItems) {
        if (node != 0)
        {
            if (parent_node != 0)
                parent_node->addChild(node);
            else
                source_data->addRootNode(node);
        }
    }
    qDebug() << "drop";
    source_data->DEBUG_PRINT();
    //endInsertRows();
    //emit layoutChanged();
    endResetModel();

    return true;
}

bool SceneGraphModel::moveRows(const QModelIndex & sourceParent, int sourceRow, int count, const QModelIndex & destinationParent, int destinationChild)
{
    beginMoveRows(sourceParent, sourceRow, sourceRow+count+1, destinationParent, destinationChild);
    qDebug() << "moveRows";
    endMoveRows();

    return true;
}

bool SceneGraphModel::insertRows(int row, int count, const QModelIndex & parent)
{
    S5::SceneNode* parent_node = getNode(parent);

    if (parent_node != 0)
    {
        beginInsertRows(parent, row, row+count-1);
        for (int i=0 ; i<count ; ++i)
        {
            S5::SceneNode* child = new S5::SceneNode("new node");
            parent_node->addChild(child);
        }
        endInsertRows();

        return true;
    }
    return false;
}

bool SceneGraphModel::removeRows(int row, int count, const QModelIndex & parent)
{
    S5::SceneNode* parent_node = getNode(parent);

    beginRemoveRows(parent, row, row+count-1);
    for (int i=0 ; i<count ; ++i)
    {
        if (parent_node != 0)
        {
            S5::SceneNode* child = parent_node->children()[row];
            parent_node->removeChild(child);
            delete child;
        }
        else
        {
            S5::SceneNode* child = source_data->rootNodes()[row];
            source_data->removeRootNode(child);
            delete child;
        }
    }
    endRemoveRows();

    return true;
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
