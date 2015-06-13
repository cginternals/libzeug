
#include <reflectionzeug/AbstractProperty.h>
#include <reflectionzeug/AbstractValue.h>
#include <reflectionzeug/AbstractCollection.h>
#include <reflectionzeug/PropertyGroup.h>


namespace reflectionzeug
{


AbstractProperty2::AbstractProperty2()
{
}

AbstractProperty2::~AbstractProperty2()
{
}

bool AbstractProperty2::isValue() const
{
    return (dynamic_cast<const AbstractValue *>(this) != nullptr);
}

bool AbstractProperty2::isCollection() const
{
    return (dynamic_cast<const AbstractCollection *>(this) != nullptr);
}

bool AbstractProperty2::isGroup() const
{
    return (dynamic_cast<const PropertyGroup *>(this) != nullptr);
}

AbstractValue * AbstractProperty2::asValue()
{
    return dynamic_cast<AbstractValue *>(this);
}

const AbstractValue * AbstractProperty2::asValue() const
{
    return dynamic_cast<const AbstractValue *>(this);
}

AbstractCollection * AbstractProperty2::asCollection()
{
    return dynamic_cast<AbstractCollection *>(this);
}

const AbstractCollection * AbstractProperty2::asCollection() const
{
    return dynamic_cast<const AbstractCollection *>(this);
}

PropertyGroup * AbstractProperty2::asGroup()
{
    return dynamic_cast<PropertyGroup *>(this);
}

const PropertyGroup * AbstractProperty2::asGroup() const
{
    return dynamic_cast<const PropertyGroup *>(this);
}


} // namespace reflectionzeug
