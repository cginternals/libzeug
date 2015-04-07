
#pragma once


#include <reflectionzeug/new/AbstractTyped.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for floating point types
*/
template <typename T>
class TypedFloatingPoint : public AbstractTyped<T>
{
public:
    template <typename... Args>
    TypedFloatingPoint(Args&&... args);

    virtual ~TypedFloatingPoint();

    virtual double toDouble() const;
    virtual bool fromDouble(double value);
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedFloatingPoint.hpp>
