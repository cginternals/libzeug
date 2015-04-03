
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

    virtual Type get() const = 0;
    virtual void set(const Type & value) = 0;

    virtual bool isReadOnly() const = 0;
};


/**
*  @brief
*    Accessor (read-only) to a typed value
*/
template <typename Type>
class Accessor<const Type>
{
public:
    Accessor();
    virtual ~Accessor();

    virtual Type get() const = 0;
    virtual void set(const Type & value) = 0;

    virtual bool isReadOnly() const = 0;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/Accessor.hpp>
