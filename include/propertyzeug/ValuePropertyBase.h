
#pragma once

#include <signalzeug/Signal.h>

#include <propertyzeug/AbstractProperty.h>

namespace zeug {
    
/** @brief
 * Part of the property hierarchy.
 * The super class of all properties that have a value.
 */

class PROPERTYZEUG_API ValuePropertyBase : public AbstractProperty
{
public:
    ValuePropertyBase(const std::string & name);
    virtual ~ValuePropertyBase();
};

} // namespace zeug
