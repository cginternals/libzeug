
#pragma once


#include <reflectionzeug/new/AbstractValue.h>


namespace reflectionzeug
{


template <class Type>
Type * AbstractValue::as()
{
    Type * typed = dynamic_cast<Type *>(this);
    assert(typed);
    return typed;
}

template <class Type>
const Type * AbstractValue::as() const
{
    const Type * typed = dynamic_cast<const Type *>(this);
    assert(typed);
    return typed;
}


} // namespace reflectionzeug
