
#pragma once


#include <reflectionzeug/new/TypedBase.h>


namespace reflectionzeug
{


/**
*  @brief
*    Class template for defining typed values in the reflection system
*/
template <typename Type, typename Accessor>
class Typed : public TypedBase<Type, Accessor>
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


#include <reflectionzeug/new/Typed.hpp>
