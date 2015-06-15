#include <reflectionzeug/StringProperty.h>

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

StringProperty::~StringProperty()
{
}

void StringProperty::accept(AbstractPropertyVisitor * visitor)
{
    StringPropertyInterface::accept(visitor);
}

std::string StringProperty::toString() const
{
    return this->value();
}

bool StringProperty::fromString(const std::string & string)
{
    this->setValue(string);
    return true;
}

} // namespace reflectionzeug
