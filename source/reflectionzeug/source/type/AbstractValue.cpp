
#include <reflectionzeug/type/AbstractValue.h>


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

/* [TODO]
Variant AbstractValue::toVariant() const
{
	return Variant();
}

bool AbstractValue::fromVariant(const Variant & value)
{
	return false;
}
*/

void AbstractValue::accept(AbstractVisitor * visitor)
{
}


} // namespace reflectionzeug
