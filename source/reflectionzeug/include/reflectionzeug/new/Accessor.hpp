
#pragma once


#include <reflectionzeug/new/Accessor.h>


namespace reflectionzeug
{


// Read/write accessor
template <typename T>
Accessor<T>::Accessor()
{
}

template <typename T>
Accessor<T>::~Accessor()
{
}


// Read-only accessor
template <typename T>
Accessor<const T>::Accessor()
{
}

template <typename T>
Accessor<const T>::~Accessor()
{
}

template <typename T>
void Accessor<const T>::set(const T & value)
{
}


} // namespace reflectionzeug
