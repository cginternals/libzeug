
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
    /**
    *  @brief
    *    Constructor
    */
    PrimitiveTypeConverter();

    /**
    *  @brief
    *    Destructor
    */
    ~PrimitiveTypeConverter();

    /**
    *  @brief
    *    Check if Type can be converted into specified target type
    *
    *  @param[in] targetType
    *    Target type id
    *
    *  @return
    *    'true', if type can be converted into the specified type, else 'false'
    */
    bool canConvert(const std::type_info & targetType) const;

    /**
    *  @brief
    *    Convert Type into specified target type
    *
    *  @param[in] value
    *    Input value
    *  @param[in] target
    *    Target value
    *  @param[in] targetType
    *    Target type id
    *
    *  @return
    *    'true', if type could be converted, else 'false'
    */
    bool convert(const Type & value, void * target, const std::type_info & targetType) const;
};


/**
*  @brief
*    Type conversion for bool
*/
template <typename Type>
class BoolConverter : public PrimitiveTypeConverter<Type>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    BoolConverter();

    /**
    *  @brief
    *    Destructor
    */
    ~BoolConverter();

    /**
    *  @brief
    *    Convert Type into specified target type
    *
    *  @param[in] value
    *    Input value
    *  @param[in] target
    *    Target value
    *  @param[in] targetType
    *    Target type id
    *
    *  @return
    *    'true', if type could be converted, else 'false'
    */
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
    /**
    *  @brief
    *    Constructor
    */
    StringConverter();

    /**
    *  @brief
    *    Destructor
    */
    ~StringConverter();

    /**
    *  @brief
    *    Check if Type can be converted into specified target type
    *
    *  @param[in] targetType
    *    Target type id
    *
    *  @return
    *    'true', if type can be converted into the specified type, else 'false'
    */
    bool canConvert(const std::type_info & targetType) const;

    /**
    *  @brief
    *    Convert Type into specified target type
    *
    *  @param[in] value
    *    Input value
    *  @param[in] target
    *    Target value
    *  @param[in] targetType
    *    Target type id
    *
    *  @return
    *    'true', if type could be converted, else 'false'
    */
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
    /**
    *  @brief
    *    Constructor
    */
    TypeConverter();

    /**
    *  @brief
    *    Destructor
    */
    ~TypeConverter();

    /**
    *  @brief
    *    Check if Type can be converted into specified target type
    *
    *  @param[in] targetType
    *    Target type id
    *
    *  @return
    *    'true', if type can be converted into the specified type, else 'false'
    */
    bool canConvert(const std::type_info & targetType) const;

    /**
    *  @brief
    *    Convert Type into specified target type
    *
    *  @param[in] value
    *    Input value
    *  @param[in] target
    *    Target value
    *  @param[in] targetType
    *    Target type id
    *
    *  @return
    *    'true', if type could be converted, else 'false'
    */
    bool convert(const Type & value, void * target, const std::type_info & targetType) const;
};

/**
*  @brief
*    Type conversion specialization for char
*/
template <>
class TypeConverter<char> : public PrimitiveTypeConverter<char>
{
};

/**
*  @brief
*    Type conversion specialization for unsigned char
*/
template <>
class TypeConverter<unsigned char> : public PrimitiveTypeConverter<unsigned char>
{
};

/**
*  @brief
*    Type conversion specialization for short
*/
template <>
class TypeConverter<short> : public PrimitiveTypeConverter<short>
{
};

/**
*  @brief
*    Type conversion specialization for unsigned short
*/
template <>
class TypeConverter<unsigned short> : public PrimitiveTypeConverter<unsigned short>
{
};

/**
*  @brief
*    Type conversion specialization for int
*/
template <>
class TypeConverter<int> : public PrimitiveTypeConverter<int>
{
};

/**
*  @brief
*    Type conversion specialization for unsigned int
*/
template <>
class TypeConverter<unsigned int> : public PrimitiveTypeConverter<unsigned int>
{
};

/**
*  @brief
*    Type conversion specialization for long
*/
template <>
class TypeConverter<long> : public PrimitiveTypeConverter<long>
{
};

/**
*  @brief
*    Type conversion specialization for unsigned long
*/
template <>
class TypeConverter<unsigned long> : public PrimitiveTypeConverter<unsigned long>
{
};

/**
*  @brief
*    Type conversion specialization for long long
*/
template <>
class TypeConverter<long long> : public PrimitiveTypeConverter<long long>
{
};

/**
*  @brief
*    Type conversion specialization for unsigned long long
*/
template <>
class TypeConverter<unsigned long long> : public PrimitiveTypeConverter<unsigned long long>
{
};

/**
*  @brief
*    Type conversion specialization for bool
*/
template <>
class TypeConverter<bool> : public BoolConverter<bool>
{
};

/**
*  @brief
*    Type conversion specialization for float
*/
template <>
class TypeConverter<float> : public PrimitiveTypeConverter<float>
{
};

/**
*  @brief
*    Type conversion specialization for double
*/
template <>
class TypeConverter<double> : public PrimitiveTypeConverter<double>
{
};

/**
*  @brief
*    Type conversion specialization for std::string
*/
template <>
class TypeConverter<std::string> : public StringConverter<std::string>
{
};
//@}


} // namespace reflectionzeug


#include <reflectionzeug/property/TypeConverter.hpp>
