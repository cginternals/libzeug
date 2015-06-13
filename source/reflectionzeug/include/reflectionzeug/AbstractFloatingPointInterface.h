
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
    AbstractFloatingPointInterface();
    virtual ~AbstractFloatingPointInterface();

    virtual double toDouble() const = 0;
    virtual bool fromDouble(double value) = 0;
};


} // namespace reflectionzeug
