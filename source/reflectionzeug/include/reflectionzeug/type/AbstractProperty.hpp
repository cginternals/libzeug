
#pragma once


#include <reflectionzeug/type/AbstractProperty.h>


namespace reflectionzeug
{


template <typename Type>
Type * AbstractProperty::as()
{
    Type * typed = dynamic_cast<Type *>(this);
    assert(typed);
    return typed;
}

template <typename Type>
const Type * AbstractProperty::as() const
{
    const Type * typed = dynamic_cast<const Type *>(this);
    assert(typed);
    return typed;
}

template <typename Type>
Type AbstractProperty::option(const std::string & key, const Type & defaultValue) const
{
    return hasOption(key) ? option(key).value<Type>(defaultValue) : defaultValue;
}


} // namespace reflectionzeug
