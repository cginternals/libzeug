
#pragma once


#include <reflectionzeug/new/TypedString.h>
#include <reflectionzeug/new/AbstractVisitor.h>


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
    // Call visitor->visit(TypedString)
    auto * typedVisitor = visitor->asVisitor<TypedString>();
    if (typedVisitor) {
        typedVisitor->visit(this);
    }

    // Call visitor->visit(AbstractStringInterface)
    auto * interfaceVisitor = visitor->asVisitor<AbstractStringInterface>();
    if (interfaceVisitor) {
        interfaceVisitor->visit(this);
    }
}


} // namespace reflectionzeug
