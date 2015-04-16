
#include <reflectionzeug/new/AbstractValue.h>


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

void AbstractValue::accept(AbstractVisitor * visitor)
{
}


} // namespace reflectionzeug
