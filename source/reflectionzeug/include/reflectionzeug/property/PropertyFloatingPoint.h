
#pragma once


#include <reflectionzeug/property/AbstractNumberProperty.h>
#include <reflectionzeug/property/AbstractFloatingPointInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Property implementation for floating point types
*/
template <typename T>
class PropertyFloatingPoint : public AbstractNumberProperty<T>, public AbstractFloatingPointInterface
{
public:
    /**
    *  @brief
    *    Constructor
    */
    template <typename... Args>
    PropertyFloatingPoint(Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~PropertyFloatingPoint();

    // Virtual AbstractFloatingPointInterface interface
    virtual double toDouble() const override;
    virtual bool fromDouble(double value) override;

    // Virtual AbstractProperty interface
    virtual void accept(AbstractVisitor * visitor) override;


protected:
    // Virtual AbstractNumberProperty interface
    virtual std::string matchRegex() const override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyFloatingPoint.hpp>
