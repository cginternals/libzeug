
#pragma once


#include <reflectionzeug/property/AbstractNumberProperty.h>
#include <reflectionzeug/property/AbstractFloatingPointInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for floating point types
*/
template <typename T>
class PropertyFloatingPoint : public AbstractNumberProperty<T>, public AbstractFloatingPointInterface
{
public:
    template <typename... Args>
    PropertyFloatingPoint(Args&&... args);

    virtual ~PropertyFloatingPoint();

    virtual double toDouble() const override;
    virtual bool fromDouble(double value) override;

    virtual void accept(AbstractVisitor * visitor) override;


protected:
    virtual std::string matchRegex() const;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyFloatingPoint.hpp>
