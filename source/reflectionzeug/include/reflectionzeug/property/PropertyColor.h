
#pragma once


#include <reflectionzeug/base/Color.h>
#include <reflectionzeug/property/AbstractPropertyValue.h>
#include <reflectionzeug/property/AbstractColorInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type Color
*/
class PropertyColor : public AbstractPropertyValue<Color>, public AbstractColorInterface
{
public:
    template <typename... Args>
    PropertyColor(Args&&... args);

    virtual ~PropertyColor();

    virtual Color toColor() const override;
    virtual bool fromColor(const Color & color) override;

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyColor.hpp>
