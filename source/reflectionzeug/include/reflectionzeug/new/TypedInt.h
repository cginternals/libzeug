
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
    virtual ~Typed();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedInt.hpp>
