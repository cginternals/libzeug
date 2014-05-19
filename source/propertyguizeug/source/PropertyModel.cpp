
#include <propertyguizeug/PropertyModel.h>

#include <iostream>

#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/Property.h>

#include <propertyguizeug/PropertyItem.h>

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
    
PropertyModel::PropertyModel(PropertyGroup * group, QObject * parent)
:   QAbstractItemModel(parent)
,   m_root(new PropertyItem(group, this))
{
    appendChildren(m_root, group);
}

PropertyModel::~PropertyModel()
{
    delete m_root;
}

QModelIndex PropertyModel::index(int row, int column, const QModelIndex & parentIndex) const
{
    if (!hasIndex(row, column, parentIndex))
        return QModelIndex();
    
    if (!parentIndex.isValid())
        return createIndex(row, column, m_root->at(row));
    
    AbstractProperty * parent = retrieveProperty(parentIndex);
    
    if (!parent->isCollection())
        return QModelIndex();
    
    AbstractProperty * property = parent->asCollection()->at(row);
    return createIndex(row, column, property);
}

QModelIndex PropertyModel::parent(const QModelIndex & index) const
{
    if (!index.isValid())
        return QModelIndex();
    
    AbstractProperty * property = retrieveProperty(index);

    if (!property->hasParent())
        return QModelIndex();
    
    AbstractPropertyCollection * parent = property->parent();

    if (parent == m_root)
        return QModelIndex();
    
    int row = parent->parent()->indexOf(parent);
    return this->createIndex(row, 0, parent);
}

int PropertyModel::rowCount(const QModelIndex & parentIndex) const
{
    if (parentIndex.column() > 0)
        return 0;
    
    AbstractProperty * property;
    if (!parentIndex.isValid())
        property = m_root;
    else
        property = retrieveProperty(parentIndex);
    
    if (!property->isCollection())
        return 0;
    
    AbstractPropertyCollection * group = property->asCollection();
    return group->count();
}

int PropertyModel::columnCount(const QModelIndex & parentIndex) const
{
    if (!parentIndex.isValid())
        return m_root->isEmpty() ? 0 : 2;
    
    AbstractProperty * property = retrieveProperty(parentIndex);
    
    if (!property->isCollection())
        return 0;
    
    return property->asCollection()->isEmpty() ? 0 : 2;
}

QVariant PropertyModel::data(const QModelIndex & index, int role) const
{
    if (!index.isValid())
        return QVariant();
    
    if (role != Qt::DisplayRole || index.column() != 0)
        return QVariant();
    
    AbstractProperty * property = retrieveProperty(index);

    return QVariant(QString::fromStdString(property->title()));
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

void PropertyModel::onValueChanged(PropertyItem * item)
{
    // emit dataChanged
}

void PropertyModel::onBeforeAdd(
    PropertyItem * item, 
    size_t position, 
    AbstractProperty * property)
{
    // beginInsertRows
}

void PropertyModel::onAfterAdd()
{
    // endInsertRows
}

void PropertyModel::onBeforeRemove(
    PropertyItem * item, 
    size_t position)
{
    // beginRemoveRows
}

void PropertyModel::onAfterRemove()
{
    // endRemoveRows
}

void PropertyModel::addChildren(PropertyItem * item, PropertyGroup * group)
{
    group->forEach([this] (AbstractProperty * property) 
    {
        if (property->isValue())
        {
            item->append(new PropertyItem(property->asValue(), this));
        }
        else if (property->isGroup())
        {
            PropertyGroup * subGroup = property->asGroup();
            PropertyItem * item = new PropertyItem(subGroup, this);
            item->append(item);
            addChildren(item, subGroup);
        }
        else
        {
            item->append(new PropertyItem(property, this));
        }
    });
}
    
QModelIndex PropertyModel::createIndex(int row, int column, AbstractProperty * property) const
{
    return QAbstractItemModel::createIndex(row, column, property);
}

} // namespace propertyguizeug
