
#include <reflectionzeug/type/TypedColor.h>

#include <reflectionzeug/type/AbstractVisitor.h>


namespace reflectionzeug
{


TypedColor::~TypedColor()
{
}

Color TypedColor::toColor() const
{
	return this->value();
}

bool TypedColor::fromColor(const Color & color)
{
    this->setValue(color);
    return true;
}

void TypedColor::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<TypedColor>(this);
    visitor->callVisitor<AbstractColorInterface>(this);
}


} // namespace reflectionzeug
