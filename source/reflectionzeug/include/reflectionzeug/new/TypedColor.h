
#pragma once


#include <reflectionzeug/Color.h>
#include <reflectionzeug/new/AbstractTyped.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type Color
*/
class TypedColor : public AbstractTyped<Color>
{
public:
    template <typename... Args>
    TypedColor(Args&&... args);

    virtual ~TypedColor();

    virtual Color toColor() const;
    virtual bool fromColor(const Color & color);
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedColor.hpp>
