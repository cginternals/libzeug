
#pragma once


#include <reflectionzeug/AbstractTyped.h>
#include <reflectionzeug/AbstractBooleanInterface.h>


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


#include <reflectionzeug/TypedBool.hpp>
