
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
    AbstractUnsignedIntegralInterface();
    virtual ~AbstractUnsignedIntegralInterface();

    virtual unsigned long long toULongLong() const = 0;
    virtual bool fromULongLong(unsigned long long integral) = 0;
};


} // namespace reflectionzeug
