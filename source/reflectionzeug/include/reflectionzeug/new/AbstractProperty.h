
#pragma once


#include <string>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Base class for properties
*/
class REFLECTIONZEUG_API AbstractProperty2
{
public:
    AbstractProperty2(const std::string & name);
    virtual ~AbstractProperty2();


protected:
    std::string m_name; /**< Property name */
};


} // namespace reflectionzeug
