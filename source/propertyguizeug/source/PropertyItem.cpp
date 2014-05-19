
#include <propertyguizeug/PropertyItem.h>

#include <functional>

#include <reflectionzeug/AbstractValueProperty.h>
#include <reflectionzeug/PropertyGroup.h>


namespace propertyguizeug
{

PropertyItem::PropertyItem(
    reflectionzeug::AbstractProperty * collection,
    PropertyModel * model)
:   m_property(property)
,   m_parent(nullptr)
{
}

PropertyItem::PropertyItem(
    reflectionzeug::AbstractValueProperty * property,
    PropertyModel * model)
:   PropertyItem(static_cast<AbstractProperty *>(property), model)
{
    m_connections << property->valueChanged.connect(std::bind(&PropertyModel::onValueChanged, model, this));
}

PropertyItem::PropertyItem(
    reflectionzeug::PropertyGroup * group,
    PropertyModel * model)
:   PropertyItem(static_cast<AbstractProperty *>(property), model)
{
    m_connections
        << group->beforeAdd.connect(std::bind(&PropertyModel::onBeforeAdd, model, this, std::placeholders::_1, std::placeholders::_2))
        << group->afterAdd.connect(std::bind(&PropertyModel::onAfterAdd, model, this))
        << group->beforeRemove.connect(std::bind(&PropertyModel::onBeforeRemove, model, this, std::placeholders::_1))
        << group->afterRemove.connect(std::bind(&PropertyModel::onAfterRemove, model, this));
}

PropertyItem::~PropertyItem()
{
    qDeleteAll(m_children);
}

reflectionzeug::AbstractProperty * PropertyItem::property() const
{
    return m_property;
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

int PropertyItem::indexOf(PropertyItem * item) const
{
    m_children.indexOf(item);
}

void PropertyItem::insertChild(size_t i, PropertyItem * item)
{
    m_children.insert(i, item);
}

bool PropertyItem::removeChild(size_t i)
{
    if (i >= m_children.count())
        return false;

    delete m_children.take(i);
    return true;
}

void PropertyItem::appendChild(PropertyItem * item)
{
    m_children.append(item);
}

} // namespace propertyguizeug
