
#pragma once


#include <reflectionzeug/type/Typed.h>


namespace reflectionzeug
{


/**
*  @brief
*    Typed property
*/
template <typename T>
class Property : public Typed<T>
{
public:
    Property(const std::string & name = "");

    template <typename... Args>
    Property(const std::string & name, Args&&... args);

    virtual ~Property();

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/Property.hpp>
