#include <reflectionzeug/ColorPropertyInterface.h>

#include <iostream>

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

void ColorPropertyInterface::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = visitor->asVisitor<ColorPropertyInterface>();

    if (typedVisitor == nullptr)
        return AbstractValueProperty::accept(visitor);

    typedVisitor->visit(this);
}
    
std::string ColorPropertyInterface::toString() const
{
    return this->toColor().toString();
}
    
bool ColorPropertyInterface::fromString(const std::string & string)
{
    bool ok;

    Color value = Color::fromString(string, &ok);
    
    if (!ok)
    {
        std::cout << "Could not read from string." << std::endl;
        return false;
    }
    
    this->fromColor(value);
    return true;
}

} // namespace reflectionzeug
