
#pragma once


#include <reflectionzeug/new/TypeBase.h>


namespace reflectionzeug
{


template <typename T, typename ACCESSOR>
TypeBase<T, ACCESSOR>::TypeBase(const ACCESSOR & accessor)
: m_accessor(accessor)
{
}

template <typename T, typename ACCESSOR>
TypeBase<T, ACCESSOR>::~TypeBase()
{
}


} // namespace reflectionzeug
