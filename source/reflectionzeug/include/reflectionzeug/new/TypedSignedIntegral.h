
#pragma once


#include <reflectionzeug/new/AbstractTyped.h>
#include <reflectionzeug/new/AbstractSignedIntegralInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for signed integral types
*/
template <typename T>
class TypedSignedIntegral : public AbstractTyped<T>, public AbstractSignedIntegralInterface
{
public:
    template <typename... Args>
    TypedSignedIntegral(Args&&... args);

    virtual ~TypedSignedIntegral();

    virtual long long toLongLong() const override;
    virtual bool fromLongLong(long long value) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedSignedIntegral.hpp>
