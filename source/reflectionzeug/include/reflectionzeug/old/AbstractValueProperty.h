#pragma once

#include <signalzeug/Signal.h>

#include <reflectionzeug/AbstractProperty.h>
#include <reflectionzeug/AbstractPropertyVisitor.h>

namespace reflectionzeug
{

class Variant;

/** 
 * \brief The super class of all properties that store a value.
 *
 * Value properties implement an adapted Visitor Pattern.  
 * Visitors inherit from the PropertyVisitor or PropertyCategoryVisitor template for each type they want to support. 
 * The visitor template implements a visit method for the passed template type. 
 * The properties check in their accept() method, wether the visitor supports their type and
 * in case it doesn't they call the super class' accept().
 * Other than the old fashioned implementation, this one can be extended.
 *
 * \see AbstractPropertyVisitor
 * \ingroup property_hierarchy
 */
class REFLECTIONZEUG_API AbstractValueProperty : public virtual AbstractProperty
{
public:
    virtual bool isValue() const;
    
    /**
     * Implements the visitor pattern.
     * \see AbstractPropertyVisitor
     * \see PropertyVisitor
     * \see PropertyCategoryVisitor
     */
    virtual void accept(AbstractPropertyVisitor * visitor);

    virtual size_t type() const = 0;
    
    virtual std::string toString() const = 0;
    virtual bool fromString(const std::string & string) = 0;
    
    signalzeug::Signal<> valueChanged;
};

} // namespace reflectionzeug
