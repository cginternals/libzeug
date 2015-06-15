
#pragma once


#include <reflectionzeug/property/AbstractPropertyValue.h>
#include <reflectionzeug/property/AbstractBooleanInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type bool
*/
class PropertyBool : public AbstractPropertyValue<bool>, public AbstractBooleanInterface
{
public:
    template <typename... Args>
    PropertyBool(Args&&... args);

    virtual ~PropertyBool();

    virtual bool toBool() const override;
    virtual bool fromBool(bool value) override;

    virtual void accept(AbstractVisitor * visitor) override;

    void toggleValue();
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyBool.hpp>
