
#pragma once


#include <reflectionzeug/type/TypedBool.h>
#include <reflectionzeug/type/AbstractVisitor.h>


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

bool TypedBool::toBool() const
{
    return this->getValue();
}

bool TypedBool::fromBool(bool value)
{
    this->setValue(value);
    return true;
}

void TypedBool::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<TypedBool>(this);
    visitor->callVisitor<AbstractBooleanInterface>(this);
}

void TypedBool::toggleValue()
{
    this->setValue(!this->getValue());
}


} // namespace reflectionzeug
