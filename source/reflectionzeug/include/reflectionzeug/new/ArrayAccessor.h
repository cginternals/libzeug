
#pragma once


#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Accessor (read/write) to a typed array-value
*/
template <typename Type, size_t Size>
class ArrayAccessor
{
public:
    ArrayAccessor();
    virtual ~ArrayAccessor();

    virtual std::array<Type, Size> getValue() const = 0;
    virtual void setValue(const std::array<Type, Size> & array) = 0;

    virtual Type getValue(size_t i) const = 0;
    virtual void setValue(size_t i, const Type & value) = 0;

    virtual bool isReadOnly() const;
};


/**
*  @brief
*    Accessor (read-only) to a typed array-value
*/
template <typename Type, size_t Size>
class ArrayAccessor<const Type, Size> : public ArrayAccessor<Type, Size>
{
public:
    ArrayAccessor();
    virtual ~ArrayAccessor();

    virtual void setValue(const std::array<Type, Size> & array) override;

    virtual void setValue(size_t i, const Type & value) override;

    virtual bool isReadOnly() const override;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/ArrayAccessor.hpp>
