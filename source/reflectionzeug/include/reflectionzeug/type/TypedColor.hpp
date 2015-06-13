
#pragma once


#include <reflectionzeug/type/TypedColor.h>
#include <reflectionzeug/type/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename... Args>
TypedColor::TypedColor(Args&&... args)
: AbstractTyped<Color>(std::forward<Args>(args)...)
{
}

TypedColor::~TypedColor()
{
}

Color TypedColor::toColor() const
{
	return this->getValue();
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
