
#pragma once


#include <reflectionzeug/type/AbstractValue.h>


namespace reflectionzeug
{


template <typename Type>
Type * AbstractValue::as()
{
    Type * typed = dynamic_cast<Type *>(this);
    assert(typed);
    return typed;
}

template <typename Type>
const Type * AbstractValue::as() const
{
    const Type * typed = dynamic_cast<const Type *>(this);
    assert(typed);
    return typed;
}

template <typename Type>
Type AbstractValue::option(const std::string & key, const Type & defaultValue) const
{
    return hasOption(key) ? option(key).value<Type>(defaultValue) : defaultValue;
}


} // namespace reflectionzeug
