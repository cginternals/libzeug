
#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/Property.h>

#include <propertyguizeug/PropertyModel.h>

using namespace reflectionzeug;
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
    
//    Property<std::vector<int>> * property = dynamic_cast<Property<std::vector<int >> *>(parent);
//    if (property) {
//        return this->createIndex(row, column, property);
//    }

    if (!parent->isGroup())
        return QModelIndex();
    
    PropertyGroup * group = parent->asGroup();
    
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

    if (parent == m_root)
        return QModelIndex();
    
    int row = parent->parent()->indexOfProperty(parent->name());
    return this->createIndex(row, 0, parent);
}

int PropertyModel::rowCount(const QModelIndex & parentIndex) const
{
    if (!parentIndex.isValid())
        return m_root->propertyCount();
    
    AbstractProperty * property = static_cast<AbstractProperty *>(parentIndex.internalPointer());
    return property->isGroup() ? property->asGroup()->propertyCount() : 0;
}

int PropertyModel::columnCount(const QModelIndex & parentIndex) const
{
    if (!parentIndex.isValid())
        return 2;
    
    AbstractProperty * property = static_cast<AbstractProperty *>(parentIndex.internalPointer());
    
    if (!property->isGroup())
        return 0;
    
    PropertyGroup * group = property->asGroup();
    
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

    Qt::ItemFlags flags = Qt::ItemIsSelectable;

    if (index.column() == 1 && !property->isGroup())
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
