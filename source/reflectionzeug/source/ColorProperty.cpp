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
