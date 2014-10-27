#include <reflectionzeug/BoolProperty.h>

#include <reflectionzeug/util.h>

namespace reflectionzeug
{

std::string BoolProperty::toString() const 
{ 
    return this->value() ? "true" : "false"; 
}

bool BoolProperty::fromString(const std::string & string)
{
    if (!util::matchesRegex(string, "(true|false)"))
        return false;

    this->setValue(string == "true");
    return true;
}

void BoolProperty::toggleValue() 
{ 
    setValue(!value()); 
}

} // namespace reflectionzeug
