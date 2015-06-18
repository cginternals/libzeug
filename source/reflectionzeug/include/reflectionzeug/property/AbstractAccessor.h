
#pragma once


#include <typeinfo>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Abstract typed value accessor
*
*    An accessor allows access to a typed value. The type of the value can be
*    accessed by type(). To check, if the value can be converted to another type,
*    use canConvert<Type>() and convert<Type>() to convert the value. Note that
*    only primitive data types are supported for automatic conversion. To provide
*    conversion for your own data types, provide a specialization of TypeConverter.
*    A copy of the accessor can be created with clone().
*/
class REFLECTIONZEUG_API AbstractAccessor
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractAccessor();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractAccessor();

    /**
    *  @brief
    *    Get value type
    *
    *  @return
    *    Type id
    */
    virtual const std::type_info & type() const = 0;

    /**
    *  @brief
    *    Clone accessor
    *
    *  @return
    *    Copy of the accessor, has to be deleted by the caller
    */
    virtual AbstractAccessor * clone() const = 0;

    /**
    *  @brief
    *    Check if type can be converted
    *
    *  @return
    *    'true' if value can be converted into type ValueType, else 'false'.
    *
    *  @remarks
    *    Conversion is only supported into primitive data types.
    *
    *  @see TypeConverter to provide conversions for your own data types.
    */
    virtual bool canConvert(const std::type_info & targetType) const = 0;

    /**
    *  @brief
    *    Convert value into given type
    *
    *  @param[in] target
    *    Pointer to target value, must be a pointer of the given target type
    *  @param[in] targetType
    *    Target data type id
    *
    *  @return
    *    'true' if value could be converted into type ValueType, else 'false'.
    *
    *  @remarks
    *    Conversion is only supported into primitive data types.
    *
    *  @see TypeConverter to provide conversions for your own data types.
    */
    virtual bool convert(void * target, const std::type_info & targetType) const = 0;
};


} // namespace reflectionzeug
