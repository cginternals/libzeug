
#pragma once


#include <string>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Interface for unsigned integral values
*/
class REFLECTIONZEUG_API AbstractUnsignedIntegralInterface
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractUnsignedIntegralInterface();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractUnsignedIntegralInterface();

    /**
    *  @brief
    *    Convert value to unsigned long long
    *
    *  @return
    *    Integral value
    */
    virtual unsigned long long toULongLong() const = 0;

    /**
    *  @brief
    *    Convert value from unsigned long long
    *
    *  @param[in] value
    *    Integral value
    *
    *  @return
    *    'true' if the value could be set, else 'false'
    */
    virtual bool fromULongLong(unsigned long long integral) = 0;
};


} // namespace reflectionzeug
