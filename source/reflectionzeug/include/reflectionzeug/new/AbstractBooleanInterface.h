
#pragma once


#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Interface for boolean values
*/
class REFLECTIONZEUG_API AbstractBooleanInterface
{
public:
    AbstractBooleanInterface();
    virtual ~AbstractBooleanInterface();

    virtual bool toBool() const = 0;
    virtual bool fromBool(bool value) = 0;
};


} // namespace reflectionzeug
