
#pragma once


#include <reflectionzeug/new/TypedBase.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation of a typed value for a specific type
*/
template <typename Type, typename Accessor>
class TypedImpl : public TypedBase<Type, Accessor>
{
public:
    TypedImpl(const Accessor & accessor);
    virtual ~TypedImpl();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedImpl.hpp>

#include <reflectionzeug/new/TypedImplInt.h>
