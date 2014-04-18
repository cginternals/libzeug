
#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/Property.h>

#include <propertyguizeug/PropertyModel.h>

using namespace reflectionzeug;

namespace
{

AbstractProperty * retrieveProperty(const QModelIndex & index)
{
    return static_cast<AbstractProperty *>(index.internalPointer());
}
    
} // namespace

namespace propertyguizeug
{
    
PropertyModel::PropertyModel(PropertyGroup * root, QObject * parent)
:   QAbstractItemModel(parent)
,   m_root(root)
{
    this->subscribeToValueChanges();
}
    
void PropertyModel::subscribeToValueChanges()
{
    // TODO subscribe to valueChanged signals
}

PropertyModel::~PropertyModel()
{
}

QModelIndex PropertyModel::index(int row, int column, const QModelIndex & parentIndex) const
{
    if (column > 1)
        return QModelIndex();

    AbstractProperty * parent;
    if (!parentIndex.isValid())
        parent = m_root;
    else
        parent = static_cast<AbstractProperty *>(parentIndex.internalPointer());

    if (!parent->isGroup())
        return QModelIndex();
    
    AbstractPropertyGroup * group = parent->asGroup();
    
    if (group->name() == "float_array")
    {
        std::cout << "float_array[" << row << "]" <<std::endl;
        std::cout.flush();
    }
    
    return this->createIndex(row, column, group->at(row));
}

QModelIndex PropertyModel::parent(const QModelIndex & index) const
{
    if (!index.isValid())
        return QModelIndex();
    
    AbstractProperty * property = static_cast<AbstractProperty *>(index.internalPointer());
    
    if (property == m_root)
        return QModelIndex();
    
    AbstractPropertyGroup * parent = property->parent();

    if (parent == m_root)
        return QModelIndex();
    
    int row = parent->parent()->indexOf(parent);
    return this->createIndex(row, 0, parent);
}

int PropertyModel::rowCount(const QModelIndex & parentIndex) const
{
    if (!parentIndex.isValid())
        return m_root->count();
    
    AbstractProperty * property = retrieveProperty(parentIndex);
    
    if (property->name() == "float_array")
    {
        std::cout << property->asGroup()->count() << std::endl;
        std::cout.flush();
        property->asGroup()->count();
    }
    
    return property->isGroup() ? property->asGroup()->count() : 0;
}

int PropertyModel::columnCount(const QModelIndex & parentIndex) const
{
    if (!parentIndex.isValid())
        return 2;
    
    AbstractProperty * property = retrieveProperty(parentIndex);
    
    if (!property->isGroup())
        return 0;
    
    AbstractPropertyGroup * group = property->asGroup();
    
    return group->isEmpty() ? 0 : 2;
}

QVariant PropertyModel::data(const QModelIndex & index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (!index.isValid())
            return QVariant();
        
        AbstractProperty * property = retrieveProperty(index);
        
        if (index.column() == 0)
            return QVariant(QString::fromStdString(property->title()));
    }
    
    return QVariant();
}
    
Qt::ItemFlags PropertyModel::flags(const QModelIndex & index) const
{
    if (!index.isValid())
        return 0;
    
    AbstractProperty * property = retrieveProperty(index);

    Qt::ItemFlags flags = Qt::ItemIsSelectable;

    if (index.column() == 1 && property->isValue())
        flags |= Qt::ItemIsEditable;

    if (property->isEnabled())
        flags |= Qt::ItemIsEnabled;
    
    return flags;
}

QVariant PropertyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (section == 0)
            return QVariant("Property");
        
        if (section == 1)
            return QVariant("Value");
    }

    return QVariant();
}

} // namespace propertyguizeug
