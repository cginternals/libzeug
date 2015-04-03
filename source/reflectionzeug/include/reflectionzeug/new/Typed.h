
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
    virtual ~Typed();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/Typed.hpp>
