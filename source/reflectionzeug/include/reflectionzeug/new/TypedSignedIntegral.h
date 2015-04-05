
#pragma once


#include <reflectionzeug/new/TypedBase.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for signed integral types
*/
template <typename T>
class TypedSignedIntegral : public TypedBase<T>
{
public:
    TypedSignedIntegral(Accessor<T> * accessor);
    virtual ~TypedSignedIntegral();

    virtual long long toLongLong() const;
    virtual bool fromLongLong(long long value);
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedSignedIntegral.hpp>
