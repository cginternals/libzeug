
#pragma once


#include <reflectionzeug/new/TypedBase.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type bool
*/
template <typename Accessor>
class TypedBool : public TypedBase<bool, Accessor>
{
public:
    TypedBool(const Accessor & accessor);
    virtual ~TypedBool();

    void toggleValue();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedBool.hpp>
