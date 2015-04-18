
#pragma once


#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


class AbstractValue;


/**
*  @brief
*    Variant typed value
*/
class REFLECTIONZEUG_API Variant2
{
public:
    /**
    *  @brief
    *    Constructor for an empty value
    */
    Variant2();

    /**
    *  @brief
    *    Copy constructor
    *
    *  @param[in] variant
    *    Variant whose value will be copied
    */
    Variant2(const Variant2 & variant);

    /**
    *  @brief
    *    Constructor for value of type int
    *
    *  @param[in] value
    *    Variant value
    */
    Variant2(int value);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Variant2();

    /**
    *  @brief
    *    Get value as integer
    *
    *  @return
    *    Integer value
    *
    *  @remarks
    *    If the value is either a signed or unsigned integral, or a floating point
    *    value, it is converted to int. Otherwise, 0 is returned.
    */
    int toInt() const;


protected:
    AbstractValue * m_value;    /**< Typed value */
};


} // namespace reflectionzeug
