
#pragma once


#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Interface for floating-point values
*/
class REFLECTIONZEUG_API AbstractFloatingPointInterface
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractFloatingPointInterface();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractFloatingPointInterface();

    /**
    *  @brief
    *    Convert value to double
    *
    *  @return
    *    Double value
    */
    virtual double toDouble() const = 0;

    /**
    *  @brief
    *    Convert value from double
    *
    *  @param[in] value
    *    Double value
    *
    *  @return
    *    'true' if the value could be set, else 'false'
    */
    virtual bool fromDouble(double value) = 0;
};


} // namespace reflectionzeug
