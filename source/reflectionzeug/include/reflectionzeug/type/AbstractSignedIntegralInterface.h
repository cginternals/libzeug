
#pragma once


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
    AbstractSignedIntegralInterface();
    virtual ~AbstractSignedIntegralInterface();

    virtual long long toLongLong() const = 0;
    virtual bool fromLongLong(long long integral) = 0;
};


} // namespace reflectionzeug
