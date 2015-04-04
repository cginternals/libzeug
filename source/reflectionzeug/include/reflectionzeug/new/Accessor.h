
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

    bool isReadOnly() const;
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
    void set(const Type & value);

    bool isReadOnly() const;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/Accessor.hpp>
