#include "scenegraphmodel.h"

#include <QEvent>
#include <QDebug>
#include <QStringList>
#include <QMimeData>

static const QString node_mime_type = "S5editor/SceneNodePtr";

SceneGraphModel::SceneGraphModel(QObject* parent, std::shared_ptr<S5::SceneGraph> source_data) :
    QAbstractItemModel(parent),
    source_data(source_data),
    index_counter(0)
{
}

S5::SceneNodePtr SceneGraphModel::getNode(const QModelIndex &index) const
{
    if (index.isValid())
    {
        return getNode(index.internalId());
    }

    return S5::SceneNodePtr();
}

S5::SceneNodePtr SceneGraphModel::getNode(quintptr index) const
{
    auto index_map_it = index_map.find(index);
    if (index_map_it != index_map.end())
        return index_map_it->second.lock();

    return S5::SceneNodePtr();
}

struct MatchSceneNode
{
    MatchSceneNode(S5::SceneNodeWPtr node) : node(node) {}
    S5::SceneNodeWPtr node;

    bool operator()(S5::SceneNodeWPtr other)
    {
        S5::SceneNode* ptr1 = node.lock().get();
        S5::SceneNode* ptr2 = other.lock().get();
        return ptr1 != 0 && ptr1 == ptr2;
    }

    bool operator()(std::pair<quintptr, S5::SceneNodeWPtr> other)
    {
        return (*this)(other.second);
    }
};

bool SceneGraphModel::findIndex(S5::SceneNodeWPtr node, quintptr& index) const
{
    auto it = std::find_if(index_map.begin(), index_map.end(), MatchSceneNode(node));
    if (it != index_map.end())
    {
        index = it->first;
        return true;
    }

    return false;
}

QModelIndex SceneGraphModel::customMakeIndex(int row, int column, S5::SceneNodeWPtr node) const
{
    quintptr make_index;
    if (! findIndex(node, make_index))
    {
        make_index = ++index_counter;
        index_map.insert(std::pair<quintptr, S5::SceneNodeWPtr>(make_index, node));
    }
    return createIndex(row, column, make_index);
}

QModelIndex SceneGraphModel::index(int row, int column, const QModelIndex& parent) const
{
    if (parent.isValid() && parent.column() != 0)
		return QModelIndex();

    S5::SceneNodePtr parentItem = getNode(parent);

    if (!parentItem)
        parentItem = source_data->rootNode();

    if((size_t)row < parentItem->children().size())
    {
        S5::SceneNodeWPtr childItem = parentItem->children()[row];
        return customMakeIndex(row, column, childItem);
    }

    return QModelIndex();
}

QModelIndex SceneGraphModel::parent(const QModelIndex& index) const
{
    S5::SceneNodePtr childItem = getNode(index);

    if (!childItem)
        return QModelIndex();

    S5::SceneNodePtr parentItem = childItem->parent();

    if (!parentItem)
		return QModelIndex();

    quintptr parent_index;
    if (findIndex(parentItem, parent_index))
    {
        const S5::SceneNodes& parent_siblings = parentItem->parent()->children();
        auto it = std::find_if(parent_siblings.begin(), parent_siblings.end(), MatchSceneNode(parentItem));
        int parent_row = it - parent_siblings.begin();
        return createIndex(parent_row, 0, parent_index);
    }

    return QModelIndex();
}

int SceneGraphModel::rowCount(const QModelIndex& parent) const
{
    S5::SceneNodePtr parentItem = getNode(parent);

    if(!parentItem)
        parentItem = source_data->rootNode();

    return parentItem->children().size();
}

int SceneGraphModel::columnCount(const QModelIndex&) const
{
    return 1;
}

QVariant SceneGraphModel::data(const QModelIndex& parent, int role) const
{
    if(role == Qt::DisplayRole || role == Qt::EditRole)
	{
        S5::SceneNodePtr node = getNode(parent);
        if(node) return QVariant(QString::fromStdString(node->name()));
	}
	return QVariant();
}

bool SceneGraphModel::setData(const QModelIndex & parent, const QVariant & value, int role)
{
    if(role == Qt::EditRole)
    {
        S5::SceneNodePtr node = getNode(parent);
        if(node)
        {
            node->setName(value.toString().toStdString());
            return true;
        }
    }
    return false;
}

Qt::ItemFlags SceneGraphModel::flags(const QModelIndex & index) const
{
    S5::SceneNodePtr node = getNode(index);
    if(node && node->parent()) // Is node and isn't root
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

    foreach (const QModelIndex &model_index, indexes) {
        S5::SceneNodePtr node = getNode(model_index);
        quintptr internal_index;
        if (node && findIndex(node, internal_index))
            stream << internal_index;
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
    QList<S5::SceneNodePtr> newItems;
    int row_count = 0;

    while (!stream.atEnd()) {
        qintptr internal_index;
        stream >> internal_index;
        S5::SceneNodePtr node = getNode(internal_index);
        if (node)
        {
            newItems << node;
            ++row_count;
        }
    }

    S5::SceneNodePtr parent_node = getNode(parent);

    int row = parent_node->children().size();

    beginResetModel();
    //emit layoutAboutToBeChanged();
    qDebug() << "beginInsertRows" << row << row+row_count-1 << parent;
    //beginInsertRows(parent, row, row+row_count-1);
    foreach (S5::SceneNodePtr node, newItems) {
        S5::SceneNode::reparentNode(parent_node, node);
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
    S5::SceneNodePtr parent_node = getNode(parent);

    if (parent_node)
    {
        beginInsertRows(parent, row, row+count-1);
        for (int i=0 ; i<count ; ++i)
        {
            S5::SceneNodePtr child = std::make_shared<S5::SceneNode>("new node");
            S5::SceneNode::reparentNode(parent_node, child);
        }
        endInsertRows();

        return true;
    }
    return false;
}

bool SceneGraphModel::removeRows(int row, int count, const QModelIndex & parent)
{
    S5::SceneNodePtr parent_node = getNode(parent);

    if (parent_node)
    {
        beginRemoveRows(parent, row, row+count-1);
        for (int i=0 ; i<count ; ++i)
        {
            S5::SceneNodePtr child = parent_node->children()[row];
            parent_node->removeChild(child);
        }
        endRemoveRows();
    }

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
