
#pragma once


#include <reflectionzeug/new/TypedImpl.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation of a typed value for type int
*/
template <typename Accessor>
class TypedImpl<int, Accessor> : public TypedBase<int, Accessor>
{
public:
    TypedImpl(const Accessor & accessor);
    virtual ~TypedImpl();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedImplInt.hpp>
