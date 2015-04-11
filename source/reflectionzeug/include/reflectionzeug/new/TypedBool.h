
#pragma once


#include <reflectionzeug/new/AbstractTyped.h>
#include <reflectionzeug/new/AbstractBooleanInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type bool
*/
class TypedBool : public AbstractTyped<bool>, public AbstractBooleanInterface
{
public:
    template <typename... Args>
    TypedBool(Args&&... args);

    virtual ~TypedBool();

    virtual bool toBool() const override;
    virtual bool fromBool(bool value) override;

    virtual void accept(AbstractVisitor * visitor) override;

    void toggleValue();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedBool.hpp>
