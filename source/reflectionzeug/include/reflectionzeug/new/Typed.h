
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

    template<class Arg1, class Arg2, class Arg3>
    Typed(Arg1 && arg1, Arg2 && arg2, Arg3 && arg3);

    template<class Arg1, class Arg2>
    Typed(Arg1 && arg1, Arg2 && arg2);

    template<class Arg1>
    Typed(Arg1 && arg1);

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

    template<class Arg1, class Arg2, class Arg3>
    Typed(Arg1 && arg1, Arg2 && arg2, Arg3 && arg3);

    template<class Arg1, class Arg2>
    Typed(Arg1 && arg1, Arg2 && arg2);

    template<class Arg1>
    Typed(Arg1 && arg1);

    virtual ~Typed();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/Typed.hpp>
