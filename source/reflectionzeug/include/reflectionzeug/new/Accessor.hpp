
#pragma once


#include <reflectionzeug/new/Accessor.h>


namespace reflectionzeug
{


// Read/write accessor
template <typename Type>
Accessor<Type>::Accessor()
{
}

template <typename Type>
Accessor<Type>::~Accessor()
{
}


// Read-only accessor
template <typename Type>
Accessor<const Type>::Accessor()
{
}

template <typename Type>
Accessor<const Type>::~Accessor()
{
}


} // namespace reflectionzeug
