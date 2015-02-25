#pragma once

#include <reflectionzeug/reflectionzeug_api.h>
#include <reflectionzeug/ValueProperty.h>

namespace reflectionzeug
{

/**
 * \brief Property implementation for bool values.
 * \ingroup property_hierarchy
 */
class BoolProperty : public ValueProperty<bool>
{
public:
    using Type = bool;

public:
    REFLECTIONZEUG_API virtual std::string toString() const;
    REFLECTIONZEUG_API virtual bool fromString(const std::string & string);

    REFLECTIONZEUG_API void toggleValue();
};

} // namespace reflectionzeug
