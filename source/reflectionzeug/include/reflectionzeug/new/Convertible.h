
#pragma once


#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Base class for types that are convertible into type T
*/
template <typename T>
class Convertible
{
public:
    Convertible();
    virtual ~Convertible();

    virtual void convertTo(T & out) = 0;
    virtual void convertFrom(const T & value) = 0;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/Convertible.hpp>
