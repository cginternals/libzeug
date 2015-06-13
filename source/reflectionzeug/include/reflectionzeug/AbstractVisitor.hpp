
#pragma once


#include <reflectionzeug/AbstractVisitor.h>
#include <reflectionzeug/Visitor.h>


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
