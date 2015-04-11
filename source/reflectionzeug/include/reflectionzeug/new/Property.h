
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
    Property2(const std::string & name, Args&&... args);

    virtual ~Property2();

    virtual std::string name() const override;
    virtual bool setName(const std::string & name) override;

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/Property.hpp>
