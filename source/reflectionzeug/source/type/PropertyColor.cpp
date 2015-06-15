
#include <reflectionzeug/type/PropertyColor.h>

#include <reflectionzeug/type/AbstractVisitor.h>


namespace reflectionzeug
{


PropertyColor::~PropertyColor()
{
}

Color PropertyColor::toColor() const
{
	return this->value();
}

bool PropertyColor::fromColor(const Color & color)
{
    this->setValue(color);
    return true;
}

void PropertyColor::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyColor>(this);
    visitor->callVisitor<AbstractColorInterface>(this);
}


} // namespace reflectionzeug
