
#pragma once


#include <reflectionzeug/new/AbstractTyped.h>
#include <reflectionzeug/new/AbstractFloatingPointInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for floating point types
*/
template <typename T>
class TypedFloatingPoint : public AbstractTyped<T>, public AbstractFloatingPointInterface
{
public:
    template <typename... Args>
    TypedFloatingPoint(Args&&... args);

    virtual ~TypedFloatingPoint();

    virtual double toDouble() const override;
    virtual bool fromDouble(double value) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedFloatingPoint.hpp>
