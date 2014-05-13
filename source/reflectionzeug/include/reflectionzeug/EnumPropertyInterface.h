
#pragma once

#include <string>
#include <vector>

#include <reflectionzeug/reflectionzeug_api.h>
#include <reflectionzeug/AbstractValueProperty.h>


namespace reflectionzeug
{

/**
 * \brief The interface for all enum properties. 
 *
 * Used to access and edit enum properties uniformly in the user interface.
 *
 * \ingroup property_hierarchy
 */
class REFLECTIONZEUG_API EnumPropertyInterface : public virtual AbstractValueProperty
{
public:
    virtual void accept(AbstractPropertyVisitor * visitor);
    
    virtual bool hasChoices() const = 0;

    virtual std::vector<std::string> stringChoices() const = 0;
    virtual std::vector<std::string> strings() const = 0;

};

} // namespace reflectionzeug
