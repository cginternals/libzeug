
#pragma once


#include <reflectionzeug/new/AbstractTyped.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type bool
*/
class TypedBool : public AbstractTyped<bool>
{
public:
    template <typename... Args>
    TypedBool(Args&&... args);

    virtual ~TypedBool();

    virtual void accept(AbstractVisitor * visitor) override;

    void toggleValue();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedBool.hpp>
