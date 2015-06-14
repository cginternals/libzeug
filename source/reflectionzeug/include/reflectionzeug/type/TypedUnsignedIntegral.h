
#pragma once


#include <reflectionzeug/type/AbstractTyped.h>
#include <reflectionzeug/type/AbstractUnsignedIntegralInterface.h>


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

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/type/TypedUnsignedIntegral.hpp>