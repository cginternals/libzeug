
#pragma once


#include <reflectionzeug/new/AbstractTyped.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for signed integral types
*/
template <typename T>
class TypedSignedIntegral : public AbstractTyped<T>
{
public:
    template <typename... Args>
    TypedSignedIntegral(Args&&... args);

    virtual ~TypedSignedIntegral();

    virtual long long toLongLong() const;
    virtual bool fromLongLong(long long value);
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedSignedIntegral.hpp>
