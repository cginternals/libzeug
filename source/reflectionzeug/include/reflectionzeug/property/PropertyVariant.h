
#pragma once


#include <reflectionzeug/property/AbstractTypedProperty.h>
#include <reflectionzeug/property/AbstractVariantInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Property implementation for type Variant
*/
template <typename T>
class PropertyVariant : public AbstractTypedProperty<T>, public AbstractVariantInterface
{
public:
    /**
    *  @brief
    *    Constructor
    */
    template <typename... Args>
    PropertyVariant(Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~PropertyVariant();

    // Virtual AbstractProperty interface
    virtual std::string toString() const override;
    virtual bool fromString(const std::string & string) override;
    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyVariant.hpp>
