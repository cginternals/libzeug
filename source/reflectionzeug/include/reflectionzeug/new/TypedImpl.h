
#pragma once


#include <reflectionzeug/specialization_helpers.h>
#include <reflectionzeug/new/TypedSignedIntegral.h>


namespace reflectionzeug
{


/**
*  @brief
*    Helper selecting the used base class based on the specific type
*/
template <typename T, typename Accessor, typename = void>
struct TypeSelector
{
};

template <typename T, typename Accessor>
struct TypeSelector<T, Accessor, EnableIf<isSignedIntegral<T>>>
{
    using Type = TypedSignedIntegral<T, Accessor>;
};


/**
*  @brief
*    Implementation of a typed value for a specific type
*/
template <typename T, typename Accessor>
class TypedImpl : public TypeSelector<T, Accessor>::Type
{
public:
    TypedImpl(const Accessor & accessor);
    virtual ~TypedImpl();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedImpl.hpp>
