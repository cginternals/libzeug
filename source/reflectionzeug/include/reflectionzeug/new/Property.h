
#pragma once


#include <reflectionzeug/new/AbstractProperty.h>
#include <reflectionzeug/new/Typed.h>


namespace reflectionzeug
{


/**
*  @brief
*    Typed property
*/
template <typename T>
class Property2 : public Typed<T>, public AbstractProperty2
{
public:
    template <typename... Args>
    Property2(Args&&... args);

    virtual ~Property2();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/Property.hpp>
