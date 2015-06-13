
#pragma once


#include <reflectionzeug/new/AbstractTyped.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for class types
*/
template <typename T>
class TypedClass : public AbstractTyped<T>
{
public:
    template <typename... Args>
    TypedClass(Args&&... args);

    virtual ~TypedClass();

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedClass.hpp>
