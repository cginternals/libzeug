
#pragma once


#include <reflectionzeug/Color.h>
#include <reflectionzeug/new/TypedBase.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type Color
*/
template <typename Accessor>
class TypedColor : public TypedBase<Color, Accessor>
{
public:
    TypedColor(const Accessor & accessor);
    virtual ~TypedColor();

    virtual Color toColor() const;
    virtual bool fromColor(const Color & color);
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedColor.hpp>
