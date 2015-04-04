
#pragma once


#include <reflectionzeug/new/TypedImpl.h>


namespace reflectionzeug
{


/**
*  @brief
*    Typed value (read/write)
*/
template <typename Type, typename Accessor>
class Typed : public TypedImpl<Type, Accessor>
{
public:
    Typed(const Accessor & accessor);

    template <typename... Args>
    Typed(Args&&... args);

    virtual ~Typed();
};


/**
*  @brief
*    Typed value (read-only)
*/
template <typename Type, typename Accessor>
class Typed<const Type, Accessor> : public TypedImpl<Type, Accessor>
{
public:
    Typed(const Accessor & accessor);

    template <typename... Args>
    Typed(Args&&... args);

    virtual ~Typed();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/Typed.hpp>
