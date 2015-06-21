
#pragma once


#include <reflectionzeug/base/Color.h>
#include <reflectionzeug/property/AbstractValueProperty.h>
#include <reflectionzeug/property/AbstractColorInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Property implementation for type Color
*/
class PropertyColor : public AbstractValueProperty<Color>, public AbstractColorInterface
{
public:
    /**
    *  @brief
    *    Constructor
    */
    template <typename... Args>
    PropertyColor(Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~PropertyColor();

    // Virtual AbstractColorInterface interface
    virtual Color toColor() const override;
    virtual bool fromColor(const Color & color) override;

    // Virtual AbstractProperty interface
    virtual std::string toString() const override;
    virtual bool fromString(const std::string & string) override;
    virtual Variant toVariant() const override;
    virtual bool fromVariant(const Variant & value) override;
    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyColor.hpp>
