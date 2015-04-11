
#pragma once


#include <reflectionzeug/new/AbstractTypedArray.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for signed integral types
*/
template <typename T, size_t Size>
class TypedArray : public AbstractTypedArray<T, Size>
{
public:
    template <typename... Args>
    TypedArray(Args&&... args);

    virtual ~TypedArray();

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedArray.hpp>
