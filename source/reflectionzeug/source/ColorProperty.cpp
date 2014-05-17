
#include <reflectionzeug/ColorProperty.h>


namespace reflectionzeug
{

ColorProperty::~ColorProperty()
{
}

void ColorProperty::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = dynamic_cast<PropertyVisitor<Color> *>(visitor);
    
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
