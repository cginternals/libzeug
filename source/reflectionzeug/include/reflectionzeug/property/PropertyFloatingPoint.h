
#pragma once


#include <reflectionzeug/property/AbstractPropertyValue.h>
#include <reflectionzeug/property/AbstractFloatingPointInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for floating point types
*/
template <typename T>
class PropertyFloatingPoint : public AbstractPropertyValue<T>, public AbstractFloatingPointInterface
{
public:
    template <typename... Args>
    PropertyFloatingPoint(Args&&... args);

    virtual ~PropertyFloatingPoint();

    virtual double toDouble() const override;
    virtual bool fromDouble(double value) override;

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyFloatingPoint.hpp>
