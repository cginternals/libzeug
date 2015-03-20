
#pragma once


#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Base class for types, defining type and accessor to value
*/
template <typename T, typename ACCESSOR>
class TypeBase
{
public:
    TypeBase(const ACCESSOR & accessor);
    virtual ~TypeBase();

protected:
    ACCESSOR m_accessor;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypeBase.hpp>
