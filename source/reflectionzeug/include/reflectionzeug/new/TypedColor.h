
#pragma once


#include <reflectionzeug/Color.h>
#include <reflectionzeug/new/AbstractTyped.h>
#include <reflectionzeug/new/AbstractColorInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type Color
*/
class TypedColor : public AbstractTyped<Color>, public AbstractColorInterface
{
public:
    template <typename... Args>
    TypedColor(Args&&... args);

    virtual ~TypedColor();

    virtual Color toColor() const override;
    virtual bool fromColor(const Color & color) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedColor.hpp>
