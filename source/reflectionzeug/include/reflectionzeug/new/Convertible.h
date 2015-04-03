
#pragma once


#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Base class for types that are convertible into type Type
*/
template <typename Type>
class Convertible
{
public:
    Convertible();
    virtual ~Convertible();

    virtual void convertTo(Type & out) = 0;
    virtual void convertFrom(const Type & value) = 0;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/Convertible.hpp>
