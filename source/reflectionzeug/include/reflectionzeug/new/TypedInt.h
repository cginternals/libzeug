
#pragma once


#include <reflectionzeug/new/Typed.h>


namespace reflectionzeug
{


/**
*  @brief
*    Class template for defining types in the reflection system
*/
template <typename Accessor>
class Typed<int, Accessor> : public TypedBase<int, Accessor>
{
public:
    Typed(const Accessor & accessor);

    template<class P1, class P2>
    Typed(P1 && arg1, P2 && arg2);

    template<class P1>
    Typed(P1 && arg1);

    virtual ~Typed();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedInt.hpp>
