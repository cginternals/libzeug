
#pragma once

#include <vector>

#include <signalzeug/Signal.h>

#include <reflectionzeug/reflectionzeug_api.h>
#include <reflectionzeug/AbstractValueProperty.h>


namespace reflectionzeug
{

/**
 * \brief The interface for all string type properties. 
 *
 * Used to access and edit string properties (regardless of the actual string class)
 * uniformly in the user interface.
 *
 * \ingroup property_hierarchy
 */
class REFLECTIONZEUG_API StringPropertyInterface : public virtual AbstractValueProperty
{
public:
    virtual void accept(AbstractPropertyVisitor * visitor);

    virtual std::string toString() const = 0;
    virtual bool fromString(const std::string & string) = 0;
};

} // namespace reflectionzeug
