
#pragma once


#include <reflectionzeug/reflectionzeug_api.h>

#include <string>


namespace reflectionzeug
{


/**
*  @brief
*    Type conversion for primitive data types
*/
template <typename Type>
class PrimitiveTypeConverter
{
public:
    PrimitiveTypeConverter();
    ~PrimitiveTypeConverter();

    bool canConvert(const std::type_info & targetType) const;
    bool convert(const Type & value, void * target, const std::type_info & targetType) const;
};


/**
*  @brief
*    Type conversion for string data types
*/
template <typename Type>
class StringConverter
{
public:
    StringConverter();
    ~StringConverter();

    bool canConvert(const std::type_info & targetType) const;
    bool convert(const Type & value, void * target, const std::type_info & targetType) const;
};


/**
*  @brief
*    Type conversion (used by Variant)
*/
template <typename Type>
class TypeConverter
{
public:
    TypeConverter();
    ~TypeConverter();

    bool canConvert(const std::type_info & targetType) const;
    bool convert(const Type & value, void * target, const std::type_info & targetType) const;
};

// Specialization for primitive types
template <>
class TypeConverter<char> : public PrimitiveTypeConverter<char>
{
};

template <>
class TypeConverter<unsigned char> : public PrimitiveTypeConverter<unsigned char>
{
};

template <>
class TypeConverter<short> : public PrimitiveTypeConverter<short>
{
};

template <>
class TypeConverter<unsigned short> : public PrimitiveTypeConverter<unsigned short>
{
};

template <>
class TypeConverter<int> : public PrimitiveTypeConverter<int>
{
};

template <>
class TypeConverter<unsigned int> : public PrimitiveTypeConverter<unsigned int>
{
};

template <>
class TypeConverter<long> : public PrimitiveTypeConverter<long>
{
};

template <>
class TypeConverter<unsigned long> : public PrimitiveTypeConverter<unsigned long>
{
};

template <>
class TypeConverter<long long> : public PrimitiveTypeConverter<long long>
{
};

template <>
class TypeConverter<unsigned long long> : public PrimitiveTypeConverter<unsigned long long>
{
};

template <>
class TypeConverter<std::string> : public StringConverter<std::string>
{
};


} // namespace reflectionzeug


#include <reflectionzeug/property/TypeConverter.hpp>
