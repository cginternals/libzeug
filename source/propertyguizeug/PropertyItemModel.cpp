
#include <propertyzeug/Property.h>
#include <propertyzeug/PropertyGroup.h>
#include <propertyguizeug/PropertyItemModel.h>

namespace propertyguizeug {
    
PropertyItemModel::PropertyItemModel(PropertyGroup * root, QObject * parent)
:   QAbstractItemModel(parent)
,   m_root(root)
{
}

PropertyItemModel::~PropertyItemModel()
{
}

QModelIndex PropertyItemModel::index(int row, int column, const QModelIndex & parentIndex) const
{
    if (column > 1)
        return QModelIndex();
    
    if (!parentIndex.isValid()) {
        if (row == 0 && column == 0)
            return this->createIndex(0, 0, m_root);
        else
            return QModelIndex();
    }

    
    AbstractProperty * property = static_cast<AbstractProperty *>(parentIndex.internalPointer());
        
    if (!property->isGroup())
        return QModelIndex();
    
    PropertyGroup * parent = property->to<PropertyGroup>();
    
    return this->createIndex(row, column, &parent->property(row));
}

QModelIndex PropertyItemModel::parent(const QModelIndex & index) const
{
    if (!index.isValid())
        return QModelIndex();
    
    AbstractProperty * property = static_cast<AbstractProperty *>(index.internalPointer());
    
    if (property == m_root)
        return QModelIndex();
    
    PropertyGroup * parent = property->parent();
    if (parent == m_root)
        return this->createIndex(0, 0, m_root);
    
    int row = parent->parent()->indexOfProperty(parent->name());
    return this->createIndex(row, 0, parent);
}

int PropertyItemModel::rowCount(const QModelIndex & parentIndex) const
{
    if (!parentIndex.isValid())
        return 1;
    
    AbstractProperty * property = static_cast<AbstractProperty *>(parentIndex.internalPointer());
    return property->isGroup() ? property->to<PropertyGroup>()->propertyCount() : 0;
}

int PropertyItemModel::columnCount(const QModelIndex & parentIndex) const
{
    if (!parentIndex.isValid())
        return 1;
    
    AbstractProperty * property = static_cast<AbstractProperty *>(parentIndex.internalPointer());
    
    if (!property->isGroup())
        return 0;
    
    PropertyGroup * group = property->to<PropertyGroup>();
    
    return group->hasProperties() ? 1 : 0;
}

QVariant PropertyItemModel::data(const QModelIndex & index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (!index.isValid())
            return QModelIndex();
        
        AbstractProperty * property = static_cast<AbstractProperty *>(index.internalPointer());
        return QVariant(QString::fromStdString(property->name()));
    } else {
        return QVariant();
    }
}
    
Qt::ItemFlags PropertyItemModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

} // namespace

