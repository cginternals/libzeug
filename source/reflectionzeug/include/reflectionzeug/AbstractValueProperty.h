
#pragma once

#include <reflectionzeug/AbstractProperty.h>
#include <reflectionzeug/AbstractPropertyVisitor.h>


namespace reflectionzeug
{

class ArrayPropertyInterface;

/** 
 * \brief The super class of all properties that store a value.
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

};

} // namespace reflectionzeug
