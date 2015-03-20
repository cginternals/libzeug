
#pragma once


#include <reflectionzeug/new/TypeInt.h>


namespace reflectionzeug
{


template <typename ACCESSOR>
Type<int, ACCESSOR>::Type(const ACCESSOR & accessor)
: TypeBase<int, ACCESSOR>(accessor)
{
}

template <typename ACCESSOR>
Type<int, ACCESSOR>::~Type()
{
}


} // namespace reflectionzeug
