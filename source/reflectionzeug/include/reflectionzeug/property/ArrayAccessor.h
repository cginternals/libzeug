
#pragma once


#include <reflectionzeug/property/Accessor.h>


namespace reflectionzeug
{


/**
*  @brief
*    Accessor (read/write) to a typed array-value
*/
template <typename Type, size_t Size>
class ArrayAccessor : public Accessor<std::array<Type, Size>>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    ArrayAccessor();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ArrayAccessor();

    /**
    *  @brief
    *    Get array element
    *
    *  @param[in] i
    *    Index into array
    *
    *  @return
    *    Value
    */
    virtual Type getElement(size_t i) const = 0;

    /**
    *  @brief
    *    Set array element
    *
    *  @param[in] i
    *    Index into array
    *  @param[in] value
    *    Value
    */
    virtual void setElement(size_t i, const Type & value) = 0;

    // Virtual Accessor<Type> interface
    virtual bool isReadOnly() const override;
};


/**
*  @brief
*    Accessor (read-only) to a typed array-value
*/
template <typename Type, size_t Size>
class ArrayAccessor<const Type, Size> : public ArrayAccessor<Type, Size>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    ArrayAccessor();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ArrayAccessor();

    // Virtual ArrayAccessor<Type, Size> interface
    virtual void setElement(size_t i, const Type & value) override;

    // Virtual Accessor<Type> interface
    virtual bool isReadOnly() const override;
    virtual void setValue(const std::array<Type, Size> & array) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/ArrayAccessor.hpp>
