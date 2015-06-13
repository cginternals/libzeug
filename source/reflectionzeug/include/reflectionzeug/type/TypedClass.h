
#pragma once


#include <reflectionzeug/type/AbstractTyped.h>


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


#include <reflectionzeug/type/TypedClass.hpp>
