
#pragma once


#include <reflectionzeug/property/Accessor.h>


namespace reflectionzeug
{


/**
*  @brief
*    Accessor (read/write) storing the direct value
*/
template <typename Type>
class AccessorValue : public Accessor<Type>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AccessorValue();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] defaultValue
    *    Default value that is set initially
    */
    AccessorValue(const Type & defaultValue);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AccessorValue();

    // Virtual AbstractAccessor interface
    virtual AbstractAccessor * clone() const override;

    // Virtual Accessor<Type> interface
    virtual Type * ptr() const override;
    virtual Type value() const override;
    virtual void setValue(const Type & value) override;


protected:
    Type m_value;   ///< The stored value
};


/**
*  @brief
*    Accessor (read-only) storing the direct value
*/
template <typename Type>
class AccessorValue<const Type> : public Accessor<const Type>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AccessorValue();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] defaultValue
    *    Default value that is set initially
    */
    AccessorValue(const Type & defaultValue);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AccessorValue();

    // Virtual AbstractAccessor interface
    virtual AbstractAccessor * clone() const override;

    // Virtual Accessor<Type> interface
    virtual Type * ptr() const override;
    virtual Type value() const override;


protected:
    Type m_value;   ///< The stored value
};


} // namespace reflectionzeug


#include <reflectionzeug/property/AccessorValue.hpp>
