
#pragma once

#include <typeinfo>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Abstract accessor base class
*/
class REFLECTIONZEUG_API AbstractAccessor
{
public:
    AbstractAccessor();
    virtual ~AbstractAccessor();

    virtual const std::type_info & type() const = 0;
    virtual AbstractAccessor * clone() const = 0;

    virtual bool canConvert(const std::type_info & targetType) const = 0;
    virtual bool convert(void * target, const std::type_info & targetType) const = 0;
};


} // namespace reflectionzeug
