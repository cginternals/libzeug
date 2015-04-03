
#pragma once


#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Base class for typed values, defining data type and accessor to value
*/
template <typename Type, typename Accessor>
class TypedBase
{
public:
    TypedBase(const Accessor & accessor);
    virtual ~TypedBase();

protected:
    Accessor m_accessor;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedBase.hpp>
