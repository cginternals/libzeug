
#pragma once


#include <reflectionzeug/new/Type.h>


namespace reflectionzeug
{


template <typename T, typename ACCESSOR>
Type<T, ACCESSOR>::Type(const ACCESSOR & accessor)
: TypeBase<T, ACCESSOR>(accessor)
{
}

template <typename T, typename ACCESSOR>
Type<T, ACCESSOR>::~Type()
{
}


} // namespace reflectionzeug
