
#pragma once


#include <reflectionzeug/type/AbstractPropertyValue.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for class types
*/
template <typename T>
class TypedClass : public AbstractPropertyValue<T>
{
public:
    template <typename... Args>
    TypedClass(Args&&... args);

    virtual ~TypedClass();

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/type/TypedClass.hpp>
