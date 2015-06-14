
#include <reflectionzeug/type/TypedBool.h>

#include <reflectionzeug/type/AbstractVisitor.h>


namespace reflectionzeug
{


TypedBool::~TypedBool()
{
}

bool TypedBool::toBool() const
{
    return this->value();
}

bool TypedBool::fromBool(bool value)
{
    this->setValue(value);
    return true;
}

void TypedBool::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<TypedBool>(this);
    visitor->callVisitor<AbstractBooleanInterface>(this);
}

void TypedBool::toggleValue()
{
    this->setValue(!this->value());
}


} // namespace reflectionzeug