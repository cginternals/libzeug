
#include <propertyguizeug/PropertyModel.h>

#include <iostream>
#include <QDebug>

#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/Property.h>

#include "PropertyItem.h"


namespace
{

propertyguizeug::PropertyItem * retrieveItem(const QModelIndex & index)
{
    return static_cast<propertyguizeug::PropertyItem *>(index.internalPointer());
}
    
} // namespace

using namespace reflectionzeug;
namespace propertyguizeug
{
    
PropertyModel::PropertyModel(PropertyGroup * group, QObject * parent)
:   QAbstractItemModel(parent)
,   m_root(new PropertyItem(group, this))
{
}

PropertyModel::~PropertyModel()
{
    delete m_root;
}

QModelIndex PropertyModel::index(int row, int column, const QModelIndex & parentIndex) const
{
    if (!hasIndex(row, column, parentIndex))
        return QModelIndex();
    
    PropertyItem * item = parentIndex.isValid() ? retrieveItem(parentIndex) : m_root;

    return createIndex(item->at(row), column);
}

QModelIndex PropertyModel::parent(const QModelIndex & index) const
{    
    PropertyItem * item = index.isValid() ? retrieveItem(index) : m_root;
    
    if (!item->hasParent())
        return QModelIndex();

    return createIndex(item->parent());
}

int PropertyModel::rowCount(const QModelIndex & parentIndex) const
{
    if (parentIndex.column() > 0)
        return 0;
    
    PropertyItem * item = parentIndex.isValid() ? retrieveItem(parentIndex) : m_root;
    
    return item->childCount();
}

int PropertyModel::columnCount(const QModelIndex & parentIndex) const
{
    PropertyItem * item = parentIndex.isValid() ? retrieveItem(parentIndex) : m_root;
    
    return item->hasChildren() ? 2 : 0;
}

QVariant PropertyModel::data(const QModelIndex & index, int role) const
{
    if (!index.isValid())
        return QVariant();
    
    if (role != Qt::DisplayRole || index.column() != 0)
        return QVariant();
    
    PropertyItem * item = retrieveItem(index);

    return QVariant(QString::fromStdString(item->property()->title()));
}
    
Qt::ItemFlags PropertyModel::flags(const QModelIndex & index) const
{
    if (!index.isValid())
        return 0;
    
    PropertyItem * item = retrieveItem(index);

    Qt::ItemFlags flags = Qt::ItemIsSelectable;

    if (index.column() == 1 && item->property()->isValue())
        flags |= Qt::ItemIsEditable;

    if (item->property()->isEnabled())
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
    QModelIndex index = createIndex(item, 1);

    emit dataChanged(index, index);
}

void PropertyModel::onBeforeAdd(
    PropertyItem * item, 
    size_t position, 
    AbstractProperty * property)
{
    beginInsertRows(createIndex(item), position, position);
    item->insertChild(position, new PropertyItem(property, this));
}

void PropertyModel::onAfterAdd()
{
    endInsertRows();
}

void PropertyModel::onBeforeRemove(
    PropertyItem * item, 
    size_t position)
{
    beginRemoveRows(createIndex(item), position, position);
    item->removeChild(position);
}

void PropertyModel::onAfterRemove()
{
    endRemoveRows();
}

QModelIndex PropertyModel::createIndex(PropertyItem * item, int column) const
{
    if (item == m_root)
        return QModelIndex();
    
    return QAbstractItemModel::createIndex(item->index(), column, item);
}

} // namespace propertyguizeug
