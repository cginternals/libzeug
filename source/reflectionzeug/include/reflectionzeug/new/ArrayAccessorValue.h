
#pragma once


#include <reflectionzeug/new/ArrayAccessor.h>


namespace reflectionzeug
{


/**
*  @brief
*    Accessor (read/write) storing the direct value
*/
template <typename Type, size_t Size>
class ArrayAccessorValue : public ArrayAccessor<Type, Size>
{
public:
    ArrayAccessorValue();
    ArrayAccessorValue(const std::array<Type, Size> & defaultValue);
    virtual ~ArrayAccessorValue();

    virtual std::array<Type, Size> getValue() const override;
    virtual void setValue(const std::array<Type, Size> & array) override;

    virtual Type getElement(size_t i) const override;
    virtual void setElement(size_t i, const Type & value) override;


protected:
    std::array<Type, Size> m_value;
};


/**
*  @brief
*    Accessor (read-only) storing the direct value
*/
template <typename Type, size_t Size>
class ArrayAccessorValue<const Type, Size> : public ArrayAccessor<const Type, Size>
{
public:
    ArrayAccessorValue();
    ArrayAccessorValue(const std::array<Type, Size> & defaultValue);
    virtual ~ArrayAccessorValue();

    virtual std::array<Type, Size> getValue() const override;

    virtual Type getElement(size_t i) const override;


protected:
    std::array<Type, Size> m_value;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/ArrayAccessorValue.hpp>
