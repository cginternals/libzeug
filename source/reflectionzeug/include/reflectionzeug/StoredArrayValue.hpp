
#pragma once

namespace reflectionzeug
{

template <typename Type, size_t Size>
StoredArrayValue<Type, Size>::StoredArrayValue(const std::array<Type, Size> & array)
:   m_array(array)
{
}

template <typename Type, size_t Size>
std::array<Type, Size> StoredArrayValue<Type, Size>::get() const
{
    return m_array;
}

template <typename Type, size_t Size>
void StoredArrayValue<Type, Size>::set(const std::array<Type, Size> & array)
{
    m_array = array;
}

template <typename Type, size_t Size>
Type StoredArrayValue<Type, Size>::get(size_t i) const
{
    return m_array.at(i);
}

template <typename Type, size_t Size>
void StoredArrayValue<Type, Size>::set(size_t i, const Type & value)
{
    m_array.at(i) = value;
}

} // namespace reflectionzeug
