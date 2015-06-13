#include "PropertyItem.h"

#include <functional>

#include <reflectionzeug/AbstractValueProperty.h>
#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/Property.h>

#include <propertyguizeug/PropertyModel.h>

using namespace reflectionzeug;
namespace propertyguizeug
{

PropertyItem::PropertyItem(
    reflectionzeug::AbstractProperty * property,
    PropertyModel * model)
:   m_property(property)
,   m_parent(nullptr)
{
    if (property->isValue())
    {
        AbstractValueProperty * value = property->asValue();
        
        m_connections.append(value->valueChanged.onFire([this, model]() { model->onValueChanged(this); }));
    }
    
    if (property->isCollection())
    {
        AbstractPropertyCollection * collection = property->asCollection();
        collection->forEach([this, model] (AbstractProperty & child) 
        {
            appendChild(new PropertyItem(&child, model));
        });

        if (collection->isGroup())
        {
            PropertyGroup * group = property->asGroup();

            m_connections.append({
                group->beforeAdd.connect([this, model](size_t position, AbstractProperty * property) { model->onBeforeAdd(this, position, property); }),
                group->afterAdd.onFire([this, model]() { model->onAfterAdd(); }),
                group->beforeRemove.connect([this, model](size_t position) { model->onBeforeRemove(this, position); }),
                group->afterRemove.onFire([this, model]() { model->onAfterRemove(); })
            });
        }
    }
}

PropertyItem::~PropertyItem()
{
    for (signalzeug::Connection & connection : m_connections)
        connection.disconnect();
        
    qDeleteAll(m_children);
}

reflectionzeug::AbstractProperty * PropertyItem::property() const
{
    return m_property;
}

int PropertyItem::index() const
{
    if (!hasParent())
        return -1;
    
    return m_parent->indexOf(this);
}
    
bool PropertyItem::isEnabled() const
{
    return m_property->option("enabled").value<bool>(true) && (hasParent() ? m_parent->isEnabled() : true);
}

bool PropertyItem::isReadOnly() const
{
    return m_property->option("readonly").value<bool>(false) || (hasParent() ? m_parent->isReadOnly() : false);
}

PropertyItem * PropertyItem::parent() const
{
    return m_parent;
}

void PropertyItem::setParent(PropertyItem * parent)
{
    m_parent = parent;
}

bool PropertyItem::hasParent() const
{
    return m_parent != nullptr;
}

bool PropertyItem::hasChildren() const
{
    return !m_children.isEmpty();
}

size_t PropertyItem::childCount() const
{
    return m_children.count();
}

PropertyItem * PropertyItem::at(size_t i) const
{
    return m_children.at(i);
}

int PropertyItem::indexOf(const PropertyItem * item) const
{
    return m_children.indexOf(const_cast<PropertyItem *>(item));
}

void PropertyItem::insertChild(size_t i, PropertyItem * item)
{
    m_children.insert(i, item);
    item->setParent(this);
}

bool PropertyItem::removeChild(size_t i)
{
    if (i >= (size_t)m_children.count())
        return false;

    delete m_children.takeAt(i);
    return true;
}

void PropertyItem::appendChild(PropertyItem * item)
{
    m_children.append(item);
    item->setParent(this);
}

} // namespace propertyguizeug
