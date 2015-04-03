
#pragma once


#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Accessor (read/write) to a typed value
*/
template <typename T>
class Accessor
{
public:
    Accessor();
    virtual ~Accessor();

    virtual T get() const = 0;
    virtual void set(const T & value) = 0;
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
    virtual void set(const Type & value);
};


} // namespace reflectionzeug


#include <reflectionzeug/new/Accessor.hpp>
