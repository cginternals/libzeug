
#pragma once


#include <reflectionzeug/property/ArrayAccessor.h>


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
    /**
    *  @brief
    *    Constructor
    */
    ArrayAccessorValue();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] defaultValue
    *    Default value that is set initially
    */
    ArrayAccessorValue(const std::array<Type, Size> & defaultValue);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ArrayAccessorValue();

    // Virtual AbstractAccessor interface
    virtual AbstractAccessor * clone() const override;

    // Virtual Accessor<Type> interface
    virtual std::array<Type, Size> * ptr() const override;
    virtual std::array<Type, Size> value() const override;
    virtual void setValue(const std::array<Type, Size> & array) override;

    // Virtual ArrayAccessor<Type, Size> interface
    virtual Type getElement(size_t i) const override;
    virtual void setElement(size_t i, const Type & value) override;


protected:
    std::array<Type, Size> m_value; ///< The stored value
};


/**
*  @brief
*    Accessor (read-only) storing the direct value
*/
template <typename Type, size_t Size>
class ArrayAccessorValue<const Type, Size> : public ArrayAccessor<const Type, Size>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    ArrayAccessorValue();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] defaultValue
    *    Default value that is set initially
    */
    ArrayAccessorValue(const std::array<Type, Size> & defaultValue);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ArrayAccessorValue();

    // Virtual AbstractAccessor interface
    virtual AbstractAccessor * clone() const override;

    // Virtual Accessor<Type> interface
    virtual std::array<Type, Size> * ptr() const override;
    virtual std::array<Type, Size> value() const override;

    // Virtual ArrayAccessor<Type, Size> interface
    virtual Type getElement(size_t i) const override;


protected:
    std::array<Type, Size> m_value; ///< The stored value
};


} // namespace reflectionzeug


#include <reflectionzeug/property/ArrayAccessorValue.hpp>
