
#include <reflectionzeug/new/AbstractValue.h>
#include <reflectionzeug/new/AbstractCollection.h>
#include <reflectionzeug/new/PropertyGroup.h>


namespace reflectionzeug
{


AbstractValue::AbstractValue()
{
}

AbstractValue::~AbstractValue()
{
}

std::string AbstractValue::name() const
{
    // Not implemented for base class
    return "";
}

bool AbstractValue::setName(const std::string & name)
{
    // Not implemented for base class
    return false;
}

bool AbstractValue::hasName() const
{
    return !name().empty();
}

AbstractCollection * AbstractValue::asCollection()
{
    return dynamic_cast<AbstractCollection *>(this);
}

const AbstractCollection * AbstractValue::asCollection() const
{
    return dynamic_cast<const AbstractCollection *>(this);
}

PropertyGroup2 * AbstractValue::asGroup()
{
    return dynamic_cast<PropertyGroup2 *>(this);
}

const PropertyGroup2 * AbstractValue::asGroup() const
{
    return dynamic_cast<const PropertyGroup2 *>(this);
}

bool AbstractValue::isCollection() const
{
    return (dynamic_cast<const AbstractCollection *>(this) != nullptr);
}

bool AbstractValue::isGroup() const
{
    return (dynamic_cast<const PropertyGroup2 *>(this) != nullptr);
}

void AbstractValue::accept(AbstractVisitor * visitor)
{
}


} // namespace reflectionzeug
