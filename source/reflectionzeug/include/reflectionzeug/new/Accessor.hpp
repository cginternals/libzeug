
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

template <typename Type>
bool Accessor<Type>::isReadOnly() const
{
    return false;
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

template <typename Type>
void Accessor<const Type>::setValue(const Type & value)
{
    // Read-only value!
}

template <typename Type>
bool Accessor<const Type>::isReadOnly() const
{
    return true;
}


} // namespace reflectionzeug
