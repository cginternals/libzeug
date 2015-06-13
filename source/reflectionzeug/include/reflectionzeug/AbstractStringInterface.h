
#pragma once


#include <string>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Interface for typed values to be accessed via strings
*/
class REFLECTIONZEUG_API AbstractStringInterface
{
public:
    AbstractStringInterface();
    virtual ~AbstractStringInterface();

    virtual std::string toString() const = 0;
    virtual bool fromString(const std::string & string) = 0;
};


} // namespace reflectionzeug
