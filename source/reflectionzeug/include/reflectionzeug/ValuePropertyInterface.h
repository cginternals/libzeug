
#pragma once

#include <reflectionzeug/AbstractProperty.h>
#include <reflectionzeug/AbstractPropertyVisitor.h>

namespace reflectionzeug
{

/** \brief Part of the property hierarchy. The super class of all properties that have a value.
 */
class REFLECTIONZEUG_API ValuePropertyInterface : public AbstractProperty
{
public:
    ValuePropertyInterface();
    ValuePropertyInterface(const std::string & name);

    virtual void accept(AbstractPropertyVisitor * visitor, bool warn = true);

    virtual size_t type() = 0;

    virtual std::string toString() const = 0;
    virtual bool fromString(const std::string & string) = 0;

    virtual bool isArray() const;
};

} // namespace reflectionzeug
