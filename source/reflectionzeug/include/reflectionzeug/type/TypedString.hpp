
#pragma once


#include <reflectionzeug/type/TypedString.h>
#include <reflectionzeug/type/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename... Args>
TypedString::TypedString(Args&&... args)
: AbstractTyped<std::string>(std::forward<Args>(args)...)
{
}

TypedString::~TypedString()
{
}

std::string TypedString::toString() const
{
    return this->getValue();
}

bool TypedString::fromString(const std::string & string)
{
    this->setValue(string);
    return true;
}

void TypedString::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<TypedString>(this);
    visitor->callVisitor<AbstractStringInterface>(this);
}


} // namespace reflectionzeug
