
#pragma once


#include <reflectionzeug/property/Accessor.h>

#include <reflectionzeug/property/TypeConverter.h>


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

template <typename Type>
const std::type_info & Accessor<Type>::type() const
{
    return typeid(Type);
}

template <typename Type>
bool Accessor<Type>::canConvert(const std::type_info & targetType) const
{
    return TypeConverter<Type>().canConvert(targetType);
}

template <typename Type>
bool Accessor<Type>::convert(void * target, const std::type_info & targetType) const
{
    return TypeConverter<Type>().convert(this->value(), target, targetType);
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
bool Accessor<const Type>::isReadOnly() const
{
    return true;
}

template <typename Type>
void Accessor<const Type>::setValue(const Type & /*value*/)
{
    // Read-only value!
}


} // namespace reflectionzeug
