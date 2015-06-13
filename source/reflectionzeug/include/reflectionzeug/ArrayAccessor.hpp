
#pragma once


#include <reflectionzeug/ArrayAccessor.h>


namespace reflectionzeug
{


// Read/write accessor
template <typename Type, size_t Size>
ArrayAccessor<Type, Size>::ArrayAccessor()
{
}

template <typename Type, size_t Size>
ArrayAccessor<Type, Size>::~ArrayAccessor()
{
}

template <typename Type, size_t Size>
bool ArrayAccessor<Type, Size>::isReadOnly() const
{
    return false;
}


// Read-only accessor
template <typename Type, size_t Size>
ArrayAccessor<const Type, Size>::ArrayAccessor()
{
}

template <typename Type, size_t Size>
ArrayAccessor<const Type, Size>::~ArrayAccessor()
{
}

template <typename Type, size_t Size>
void ArrayAccessor<const Type, Size>::setValue(const std::array<Type, Size> & array)
{
    // Read-only value!
}

template <typename Type, size_t Size>
void ArrayAccessor<const Type, Size>::setElement(size_t i, const Type & value)
{
    // Read-only value!
}

template <typename Type, size_t Size>
bool ArrayAccessor<const Type, Size>::isReadOnly() const
{
    return true;
}


} // namespace reflectionzeug
