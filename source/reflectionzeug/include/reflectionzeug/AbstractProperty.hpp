
#pragma once


#include <reflectionzeug/AbstractProperty.h>


namespace reflectionzeug
{


template <class Type>
Type * AbstractProperty::as()
{
    Type * typed = dynamic_cast<Type *>(this);
    assert(typed);
    return typed;
}

template <class Type>
const Type * AbstractProperty::as() const
{
    const Type * typed = dynamic_cast<const Type *>(this);
    assert(typed);
    return typed;
}


} // namespace reflectionzeug
