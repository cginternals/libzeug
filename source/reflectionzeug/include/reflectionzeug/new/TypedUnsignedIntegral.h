
#pragma once


#include <reflectionzeug/new/AbstractTyped.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for unsigned integral types
*/
template <typename T>
class TypedUnsignedIntegral : public AbstractTyped<T>
{
public:
    template <typename... Args>
    TypedUnsignedIntegral(Args&&... args);

    virtual ~TypedUnsignedIntegral();

    virtual unsigned long long toULongLong() const;
    virtual bool fromULongLong(unsigned long long value);
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedUnsignedIntegral.hpp>
