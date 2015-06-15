#include <reflectionzeug/ColorProperty.h>

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

ColorProperty::~ColorProperty()
{
}

void ColorProperty::accept(AbstractPropertyVisitor * visitor)
{
    ColorPropertyInterface::accept(visitor);
}

std::string ColorProperty::toString() const
{
    return this->value().toString();
}
    
bool ColorProperty::fromString(const std::string & string)
{
    bool ok;
    Color value = Color::fromString(string, &ok);
    
    if (!ok)
        return false;
    
    this->setValue(value);
    return true;
}

Color ColorProperty::toColor() const
{
    return this->value();
}

bool ColorProperty::fromColor(const Color & color)
{
    this->setValue(color);
    return true;
}

} // namespace reflectionzeug
