
#include <reflectionzeug/new/AbstractProperty.h>
#include <reflectionzeug/new/AbstractValue.h>
#include <reflectionzeug/new/AbstractCollection.h>
#include <reflectionzeug/new/PropertyGroup.h>


namespace reflectionzeug
{


AbstractProperty2::AbstractProperty2()
{
}

AbstractProperty2::AbstractProperty2(const std::string & name)
: m_name(name)
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
    return (dynamic_cast<const PropertyGroup2 *>(this) != nullptr);
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

PropertyGroup2 * AbstractProperty2::asGroup()
{
    return dynamic_cast<PropertyGroup2 *>(this);
}

const PropertyGroup2 * AbstractProperty2::asGroup() const
{
    return dynamic_cast<const PropertyGroup2 *>(this);
}


} // namespace reflectionzeug
