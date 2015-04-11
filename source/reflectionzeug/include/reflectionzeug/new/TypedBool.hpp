
#pragma once


#include <reflectionzeug/new/TypedBool.h>
#include <reflectionzeug/new/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename... Args>
TypedBool::TypedBool(Args&&... args)
: AbstractTyped<bool>(std::forward<Args>(args)...)
{
}

TypedBool::~TypedBool()
{
}

void TypedBool::accept(AbstractVisitor * visitor)
{
    // Call visitor->visit(TypedBool)
    auto * typedVisitor = visitor->asVisitor<TypedBool>();
    if (typedVisitor) {
        typedVisitor->visit(this);
    }
}

void TypedBool::toggleValue()
{
	this->setValue(!this->getValue());
}


} // namespace reflectionzeug
