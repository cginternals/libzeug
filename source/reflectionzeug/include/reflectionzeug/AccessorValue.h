
#pragma once


#include <reflectionzeug/Accessor.h>


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
    AccessorValue();
    AccessorValue(const Type & defaultValue);
    virtual ~AccessorValue();

    virtual Type getValue() const override;
    virtual void setValue(const Type & value) override;


protected:
    Type m_value;
};


/**
*  @brief
*    Accessor (read-only) storing the direct value
*/
template <typename Type>
class AccessorValue<const Type> : public Accessor<const Type>
{
public:
    AccessorValue();
    AccessorValue(const Type & defaultValue);
    virtual ~AccessorValue();

    virtual Type getValue() const override;


protected:
    Type m_value;
};


} // namespace reflectionzeug


#include <reflectionzeug/AccessorValue.hpp>
