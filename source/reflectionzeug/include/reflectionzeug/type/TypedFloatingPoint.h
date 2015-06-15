
#pragma once


#include <reflectionzeug/type/AbstractPropertyValue.h>
#include <reflectionzeug/type/AbstractFloatingPointInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for floating point types
*/
template <typename T>
class TypedFloatingPoint : public AbstractPropertyValue<T>, public AbstractFloatingPointInterface
{
public:
    template <typename... Args>
    TypedFloatingPoint(Args&&... args);

    virtual ~TypedFloatingPoint();

    virtual double toDouble() const override;
    virtual bool fromDouble(double value) override;

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/type/TypedFloatingPoint.hpp>
