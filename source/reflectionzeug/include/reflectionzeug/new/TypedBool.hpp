
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
    // Call visitor->visit(TypedBool)
    auto * typedVisitor = visitor->asVisitor<TypedBool>();
    if (typedVisitor) {
        typedVisitor->visit(this);
    }

    // Call visitor->visit(AbstractBooleanInterface)
    auto * interfaceVisitor = visitor->asVisitor<AbstractBooleanInterface>();
    if (interfaceVisitor) {
        interfaceVisitor->visit(this);
    }
}

void TypedBool::toggleValue()
{
    this->setValue(!this->getValue());
}


} // namespace reflectionzeug
