
#pragma once


#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Accessor (read/write) to a typed value
*/
template <typename Type>
class Accessor
{
public:
    Accessor();
    virtual ~Accessor();

    virtual Type getValue() const = 0;
    virtual void setValue(const Type & value) = 0;

    virtual bool isReadOnly() const;
};


/**
*  @brief
*    Accessor (read-only) to a typed value
*/
template <typename Type>
class Accessor<const Type> : public Accessor<Type>
{
public:
    Accessor();
    virtual ~Accessor();

    virtual void setValue(const Type & value) override;

    virtual bool isReadOnly() const override;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/Accessor.hpp>