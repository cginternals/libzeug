
#pragma once


#include <reflectionzeug/property/AbstractProperty.h>

#include <cassert>


namespace reflectionzeug
{


template <typename Type>
Type * AbstractProperty::as()
{
    Type * typed = dynamic_cast<Type *>(this);

    return typed;
}

template <typename Type>
const Type * AbstractProperty::as() const
{
    const Type * typed = dynamic_cast<const Type *>(this);

    return typed;
}

template <typename Type>
Type AbstractProperty::option(const std::string & key, const Type & defaultValue) const
{
    return hasOption(key) ? option(key).value<Type>(defaultValue) : defaultValue;
}


} // namespace reflectionzeug
