
#pragma once

#include <reflectionzeug/AbstractProperty.h>

namespace reflectionzeug
{
    
/** \brief Part of the property hierarchy. The super class of all properties that have a value.
 */
class REFLECTIONZEUG_API ValueProperty : public AbstractProperty
{
public:
    ValueProperty(const std::string & name);
    virtual ~ValueProperty();

    virtual std::string valueAsString() const = 0;
    virtual void accept(AbstractPropertyVisitor & visitor) = 0;
};

} // namespace reflectionzeug
