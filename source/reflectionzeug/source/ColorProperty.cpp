#include <reflectionzeug/ColorProperty.h>

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

ColorProperty::~ColorProperty()
{
}

void ColorProperty::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = visitor->asVisitor<Property<Color>>();
    
    if (typedVisitor == nullptr)
        return ColorPropertyInterface::accept(visitor);
    
    typedVisitor->visit(reinterpret_cast<Property<Color> *>(this));
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
