
#pragma once


#include <reflectionzeug/new/TypedColor.h>
#include <reflectionzeug/new/AbstractVisitor.h>


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
    // Call visitor->visit(TypedColor)
    auto * typedVisitor = visitor->asVisitor<TypedColor>();
    if (typedVisitor) {
        typedVisitor->visit(this);
    }

    // Call visitor->visit(AbstractColorInterface)
    auto * interfaceVisitor = visitor->asVisitor<AbstractColorInterface>();
    if (interfaceVisitor) {
        interfaceVisitor->visit(this);
    }
}


} // namespace reflectionzeug
