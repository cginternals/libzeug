
#pragma once


#include <reflectionzeug/new/AbstractTyped.h>
#include <reflectionzeug/new/AbstractUnsignedIntegralInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for unsigned integral types
*/
template <typename T>
class TypedUnsignedIntegral : public AbstractTyped<T>, public AbstractUnsignedIntegralInterface
{
public:
    template <typename... Args>
    TypedUnsignedIntegral(Args&&... args);

    virtual ~TypedUnsignedIntegral();

    virtual unsigned long long toULongLong() const override;
    virtual bool fromULongLong(unsigned long long value) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedUnsignedIntegral.hpp>
