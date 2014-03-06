
#pragma once

#include <reflectionzeug/AbstractProperty.h>
#include <reflectionzeug/AbstractPropertyVisitor.h>

namespace reflectionzeug
{
    
/** \brief Part of the property hierarchy. The super class of all properties that have a value.
 */
class REFLECTIONZEUG_API ValueProperty : public AbstractProperty
{
public:
    ValueProperty(const std::string & name);

    virtual void accept(AbstractPropertyVisitor * visitor, bool warn = true) = 0;
    virtual std::string valueAsString() const = 0;

};

} // namespace reflectionzeug
