
#pragma once


#include <reflectionzeug/new/AbstractVisitor.h>
#include <reflectionzeug/new/Visitor.h>


namespace reflectionzeug
{


template <typename Type>
Visitor<Type> * AbstractVisitor::asVisitor()
{
    return dynamic_cast<Visitor<Type> *>(this);
}

template <typename Type>
Visitor<Type> * AbstractVisitor::asVisitor() const
{
    return dynamic_cast<Visitor<Type> *>(this);
}

template <typename Type>
void AbstractVisitor::callVisitor(Type * instance)
{
    auto * typedVisitor = dynamic_cast<Visitor<Type> *>(this);
    if (typedVisitor) {
        typedVisitor->visit(instance);
    }
}


} // namespace reflectionzeug
