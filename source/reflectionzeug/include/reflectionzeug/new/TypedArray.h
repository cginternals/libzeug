
#pragma once


#include <reflectionzeug/new/TypedBase.h>
#include <reflectionzeug/new/ArrayAccessor.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for signed integral types
*/
template <typename T, size_t Size>
class TypedArray : public TypedBase<std::array<T, Size>>
{
public:
    TypedArray(ArrayAccessor<T, Size> * accessor);
    virtual ~TypedArray();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedArray.hpp>
