
#pragma once 

#include <reflectionzeug/PropertyCategoryVisitor.h>

namespace reflectionzeug
{

template <typename Type>
ArrayPropertyInterface<Type>::~ArrayPropertyInterface()
{
}

template <typename Type>
void ArrayPropertyInterface<Type>::accept(AbstractPropertyVisitor * visitor, bool warn)
{
    auto * typedVisitor = dynamic_cast<PropertyCategoryVisitor<ArrayPropertyInterface> *>(visitor);

    if (typedVisitor == nullptr)
    {
        ValuePropertyInterface::accept(visitor, warn);
        return;
    }

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
