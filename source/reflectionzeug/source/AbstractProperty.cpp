
#include <reflectionzeug/type/AbstractValue.h>
#include <reflectionzeug/type/AbstractCollection.h>
#include <reflectionzeug/AbstractProperty.h>
#include <reflectionzeug/PropertyGroup.h>


namespace reflectionzeug
{


AbstractProperty::AbstractProperty()
{
}

AbstractProperty::~AbstractProperty()
{
}

bool AbstractProperty::isValue() const
{
    return (dynamic_cast<const AbstractValue *>(this) != nullptr);
}

bool AbstractProperty::isCollection() const
{
    return (dynamic_cast<const AbstractCollection *>(this) != nullptr);
}

bool AbstractProperty::isGroup() const
{
    return (dynamic_cast<const PropertyGroup *>(this) != nullptr);
}

AbstractValue * AbstractProperty::asValue()
{
    return dynamic_cast<AbstractValue *>(this);
}

const AbstractValue * AbstractProperty::asValue() const
{
    return dynamic_cast<const AbstractValue *>(this);
}

AbstractCollection * AbstractProperty::asCollection()
{
    return dynamic_cast<AbstractCollection *>(this);
}

const AbstractCollection * AbstractProperty::asCollection() const
{
    return dynamic_cast<const AbstractCollection *>(this);
}

PropertyGroup * AbstractProperty::asGroup()
{
    return dynamic_cast<PropertyGroup *>(this);
}

const PropertyGroup * AbstractProperty::asGroup() const
{
    return dynamic_cast<const PropertyGroup *>(this);
}


} // namespace reflectionzeug
