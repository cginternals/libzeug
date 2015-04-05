
#pragma once


#include <reflectionzeug/Color.h>
#include <reflectionzeug/new/TypedBase.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type Color
*/
class TypedColor : public TypedBase<Color>
{
public:
    TypedColor(Accessor<Color> * accessor);
    virtual ~TypedColor();

    virtual Color toColor() const;
    virtual bool fromColor(const Color & color);
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedColor.hpp>
