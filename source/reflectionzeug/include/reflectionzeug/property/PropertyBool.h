
#pragma once


#include <reflectionzeug/property/AbstractValueProperty.h>
#include <reflectionzeug/property/AbstractBooleanInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type bool
*/
class PropertyBool : public AbstractValueProperty<bool>, public AbstractBooleanInterface
{
public:
    template <typename... Args>
    PropertyBool(Args&&... args);

    virtual ~PropertyBool();

    virtual bool toBool() const override;
    virtual bool fromBool(bool value) override;

    virtual std::string toString() const override;
    virtual bool fromString(const std::string & string) override;

    virtual void accept(AbstractVisitor * visitor) override;

    void toggleValue();
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyBool.hpp>
