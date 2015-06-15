
#include <reflectionzeug/property/PropertyBool.h>

#include <reflectionzeug/property/AbstractVisitor.h>


namespace reflectionzeug
{


PropertyBool::~PropertyBool()
{
}

bool PropertyBool::toBool() const
{
    return this->value();
}

bool PropertyBool::fromBool(bool value)
{
    this->setValue(value);
    return true;
}

void PropertyBool::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyBool>(this);
    visitor->callVisitor<AbstractBooleanInterface>(this);
}

void PropertyBool::toggleValue()
{
    this->setValue(!this->value());
}


} // namespace reflectionzeug
