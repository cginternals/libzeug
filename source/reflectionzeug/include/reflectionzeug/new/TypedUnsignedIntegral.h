
#pragma once


#include <reflectionzeug/new/TypedBase.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for unsigned integral types
*/
template <typename T, typename Accessor>
class TypedUnsignedIntegral : public TypedBase<T, Accessor>
{
public:
    TypedUnsignedIntegral(const Accessor & accessor);
    virtual ~TypedUnsignedIntegral();

    virtual unsigned long long toULongLong() const;
    virtual bool fromULongLong(unsigned long long value);
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedUnsignedIntegral.hpp>
