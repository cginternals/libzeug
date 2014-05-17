
#pragma once

#include <reflectionzeug/reflectionzeug_api.h>
#include <reflectionzeug/AbstractValueProperty.h>
#include <reflectionzeug/Color.h>


namespace reflectionzeug
{

/**
 * \brief The interface for all color type properties. 
 *
 * Used to access and edit color properties (regardless of the actual color class)
 * uniformly in the user interface.
 *
 * \ingroup property_hierarchy
 */
class REFLECTIONZEUG_API ColorPropertyInterface : public virtual AbstractValueProperty
{
public:
    virtual void accept(AbstractPropertyVisitor * visitor);
    
    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);

    virtual Color toColor() const = 0;
    virtual bool fromColor(const Color & color) = 0;
};

} // namespace reflectionzeug
