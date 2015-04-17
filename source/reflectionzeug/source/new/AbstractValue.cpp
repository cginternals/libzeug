
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

bool AbstractValue::hasName() const
{
    return !name().empty();
}

void AbstractValue::accept(AbstractVisitor * visitor)
{
}


} // namespace reflectionzeug
