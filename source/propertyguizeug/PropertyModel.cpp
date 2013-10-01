
#include <propertyguizeug/PropertyModel.h>

#include <propertyzeug/PropertyGroup.h>

namespace propertyguizeug {
    
using propertyzeug::AbstractProperty;
    
PropertyModel::PropertyModel(PropertyGroup * root, QObject * parent)
:   QAbstractItemModel(parent)
,   m_root(root)
{
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
    
    PropertyGroup * group = parent->to<PropertyGroup>();
    
    return this->createIndex(row, column, group->property(row));
}

QModelIndex PropertyModel::parent(const QModelIndex & index) const
{
    if (!index.isValid())
        return QModelIndex();
    
    AbstractProperty * property = static_cast<AbstractProperty *>(index.internalPointer());
    
    if (property == m_root)
        return QModelIndex();
    
    PropertyGroup * parent = property->parent();
    
    int row;
    if (parent == m_root)
        row = 0;
    else
        row = parent->parent()->indexOfProperty(parent->name());
    
    return this->createIndex(row, 0, parent);
}

int PropertyModel::rowCount(const QModelIndex & parentIndex) const
{
    if (!parentIndex.isValid())
        return m_root->propertyCount();
    
    AbstractProperty * property = static_cast<AbstractProperty *>(parentIndex.internalPointer());
    return property->isGroup() ? property->to<PropertyGroup>()->propertyCount() : 0;
}

int PropertyModel::columnCount(const QModelIndex & parentIndex) const
{
    if (!parentIndex.isValid())
        return 2;
    
    AbstractProperty * property = static_cast<AbstractProperty *>(parentIndex.internalPointer());
    
    if (!property->isGroup())
        return 0;
    
    PropertyGroup * group = property->to<PropertyGroup>();
    
    return group->hasProperties() ? 2 : 0;
}

QVariant PropertyModel::data(const QModelIndex & index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (!index.isValid())
            return QVariant();
        
        AbstractProperty * property = static_cast<AbstractProperty *>(index.internalPointer());
        
        if (index.column() == 0)
            return QVariant(QString::fromStdString(property->title()));
    }
    
    return QVariant();
}
    
Qt::ItemFlags PropertyModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    
    AbstractProperty * property = static_cast<AbstractProperty *>(index.internalPointer());
    
    Qt::ItemFlags flags = Qt::ItemIsEnabled;

    if (index.column() == 1 && !property->isGroup())
        flags |= Qt::ItemIsEditable;
    
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

} // namespace

