
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
        
        m_connections.append(value->valueChanged.onFire(std::bind(&PropertyModel::onValueChanged, model, this)));
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
                group->beforeAdd.connect(std::bind(&PropertyModel::onBeforeAdd, model, this, std::placeholders::_1, std::placeholders::_2)),
                group->afterAdd.onFire(std::bind(&PropertyModel::onAfterAdd, model)),
                group->beforeRemove.connect(std::bind(&PropertyModel::onBeforeRemove, model, this, std::placeholders::_1)),
                group->afterRemove.onFire(std::bind(&PropertyModel::onAfterRemove, model))
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
    if (!hasParent())
        return !m_property->flagSet("disabled");
        
    return !m_property->flagSet("disabled") && m_parent->isEnabled();
}

bool PropertyItem::isReadOnly() const
{
    if (!hasParent())
        return m_property->flagSet("readonly");
        
    return m_property->flagSet("readonly") || m_parent->isReadOnly();
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
    if (i >= m_children.count())
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
