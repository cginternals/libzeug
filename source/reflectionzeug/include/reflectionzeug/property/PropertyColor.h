
#pragma once


#include <reflectionzeug/base/Color.h>
#include <reflectionzeug/property/AbstractTypedProperty.h>
#include <reflectionzeug/property/AbstractColorInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Property implementation for type Color
*/
template <typename T>
class PropertyColor : public AbstractTypedProperty<T>, public AbstractColorInterface
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
    virtual void getRGBA(int & r, int & g, int & b, int & a) const override;
    virtual void setRGBA(int r, int g, int b, int a) override;
    virtual int red() const override;
    virtual void setRed(int red) override;
    virtual int green() const override;
    virtual void setGreen(int green) override;
    virtual int blue() const override;
    virtual void setBlue(int blue) override;
    virtual int alpha() const override;
    virtual void setAlpha(int alpha) override;

    // Virtual AbstractProperty interface
    virtual std::string toString() const override;
    virtual bool fromString(const std::string & string) override;
    virtual Variant toVariant() const override;
    virtual bool fromVariant(const Variant & value) override;
    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyColor.hpp>
