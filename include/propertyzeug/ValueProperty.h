
#pragma once

#include <propertyzeug/AbstractProperty.h>

namespace zeug 
{
    
/** \brief Part of the property hierarchy. The super class of all properties that have a value.
 */
class PROPERTYZEUG_API ValueProperty : public AbstractProperty
{
public:
    ValueProperty(const std::string & name);
    virtual ~ValueProperty();

    virtual std::string valueAsString() const = 0;
    virtual void accept(AbstractPropertyVisitor & visitor) = 0;
};

} // namespace zeug
