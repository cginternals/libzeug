
#include <reflectionzeug/property/PropertyBool.h>

#include <reflectionzeug/base/util.h>
#include <reflectionzeug/property/AbstractVisitor.h>


namespace reflectionzeug
{


PropertyBool::~PropertyBool()
{
}

void PropertyBool::toggleValue()
{
    this->setValue(!this->value());
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

std::string PropertyBool::toString() const
{
    return this->value() ? "true" : "false"; 
}

bool PropertyBool::fromString(const std::string & string)
{
    if (!util::matchesRegex(string, "(true|false)"))
        return false;

    this->setValue(string == "true");
    return true;
}

void PropertyBool::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyBool>(this);
    visitor->callVisitor<AbstractBooleanInterface>(this);
}


} // namespace reflectionzeug
