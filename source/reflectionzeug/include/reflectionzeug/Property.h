
#pragma once


#include <reflectionzeug/AbstractProperty.h>
#include <reflectionzeug/NamedTyped.h>


namespace reflectionzeug
{


/**
*  @brief
*    Typed property
*/
template <typename T>
class Property2 : public NamedTyped<T>, public AbstractProperty
{
public:
    template <typename... Args>
    Property2(const std::string & name, Args&&... args);

    virtual ~Property2();

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/Property.hpp>
