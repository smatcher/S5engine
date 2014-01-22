#include "scenegraphmodel.h"

#include <QEvent>
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

    return source_data->rootNode();
}

S5::SceneNodePtr SceneGraphModel::getNode(quintptr index) const
{
    auto index_map_it = index_map.find(index);
    if (index_map_it != index_map.end())
        return index_map_it->second.lock();

    return source_data->rootNode();
}

struct MatchSceneNode
{
    MatchSceneNode(S5::SceneNodeWPtr node) : node(node) {}
    S5::SceneNodeWPtr node;

    bool operator()(S5::SceneNodeWPtr other)
    {
        S5::SceneNode* ptr1 = node.lock().get();
        S5::SceneNode* ptr2 = other.lock().get();
        return ptr1 != nullptr && ptr1 == ptr2;
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
    S5::SceneNodePtr parentItem = childItem->parent();

    if (!parentItem)
		return QModelIndex();

    quintptr parent_index;
    if (findIndex(parentItem, parent_index))
    {
        const S5::SceneNodeSet& parent_siblings = parentItem->parent()->children();
        auto it = std::find_if(parent_siblings.begin(), parent_siblings.end(), MatchSceneNode(parentItem));
        int parent_row = it - parent_siblings.begin();
        return createIndex(parent_row, 0, parent_index);
    }

    return QModelIndex();
}

int SceneGraphModel::rowCount(const QModelIndex& parent) const
{
    S5::SceneNodePtr parentItem = getNode(parent);
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
        return QVariant(QString::fromStdString(node->name()));
	}
	return QVariant();
}

bool SceneGraphModel::setData(const QModelIndex & parent, const QVariant & value, int role)
{
    if(role == Qt::EditRole)
    {
        S5::SceneNodePtr node = getNode(parent);
        if(node && node->parent()) // Is node and isn't root
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
        stream << model_index.row();
        stream << model_index.internalId();
    }

    mimeData->setData(node_mime_type, encodedData);
    return mimeData;
}

bool SceneGraphModel::dropMimeData(const QMimeData *data,
    Qt::DropAction action, int /*row*/, int column, const QModelIndex &destination_parent)
{
    if (action == Qt::IgnoreAction)
        return true;

    if (!data->hasFormat(node_mime_type))
        return false;

    if (column > 0)
        return false;

    S5::SceneNodePtr parent_node = getNode(destination_parent);
    QByteArray encodedData = data->data(node_mime_type);
    QDataStream stream(&encodedData, QIODevice::ReadOnly);

    while (!stream.atEnd()) {
        int row;
        quintptr internal_id;

        stream >> row;
        stream >> internal_id;

        QModelIndex model_index = createIndex(row, 0, internal_id);
        QModelIndex source_parent = parent(model_index);
        int destination_row = parent_node->children().size();
        int source_row = model_index.row();

        moveRow(source_parent, source_row, destination_parent, destination_row);
    }

    return false;
}

bool SceneGraphModel::moveRows(const QModelIndex & sourceParent, int sourceRow, int count, const QModelIndex & destinationParent, int destinationChild)
{
    S5::SceneNodePtr source_parent = getNode(sourceParent);
    S5::SceneNodePtr destination_parent = getNode(destinationParent);

    if (source_parent == destination_parent)
        return false;

    beginMoveRows(sourceParent, sourceRow, sourceRow+count-1, destinationParent, destinationChild);
    for (int i=0 ; i<count ; ++i)
    {
        S5::SceneNodePtr node = source_parent->children()[sourceRow];
        S5::SceneNode::reparentNode(destination_parent, node);
    }
    //source_data->DEBUG_PRINT();
    endMoveRows();

    return true;
}

bool SceneGraphModel::insertRows(int row, int count, const QModelIndex & parent)
{
    S5::SceneNodePtr parent_node = getNode(parent);

    beginInsertRows(parent, row, row+count-1);
    for (int i=0 ; i<count ; ++i)
    {
        S5::SceneNodePtr child = std::make_shared<S5::SceneNode>("new node");
        S5::SceneNode::reparentNode(parent_node, child);
    }
    endInsertRows();

    return true;
}

bool SceneGraphModel::removeRows(int row, int count, const QModelIndex & parent)
{
    S5::SceneNodePtr parent_node = getNode(parent);

    beginRemoveRows(parent, row, row+count-1);
    for (int i=0 ; i<count ; ++i)
    {
        S5::SceneNodePtr child = parent_node->children()[row];
        parent_node->removeChild(child);
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
