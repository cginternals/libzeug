
#pragma once


#include <reflectionzeug/type/Typed.h>
#include <reflectionzeug/type/NamedTyped.h>
#include <reflectionzeug/AbstractProperty.h>


namespace reflectionzeug
{


/**
*  @brief
*    Typed property
*/
template <typename T>
class Property : public NamedTyped<T>, public AbstractProperty
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args);

    virtual ~Property();

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/Property.hpp>
