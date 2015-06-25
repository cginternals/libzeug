
#pragma once


#include <string>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Interface for signed integral values
*/
class REFLECTIONZEUG_API AbstractSignedIntegralInterface
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractSignedIntegralInterface();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractSignedIntegralInterface();

    /**
    *  @brief
    *    Convert value to long long
    *
    *  @return
    *    Integral value
    */
    virtual long long toLongLong() const = 0;

    /**
    *  @brief
    *    Convert value from long long
    *
    *  @param[in] value
    *    Integral value
    *
    *  @return
    *    'true' if the value could be set, else 'false'
    */
    virtual bool fromLongLong(long long integral) = 0;
};


} // namespace reflectionzeug
