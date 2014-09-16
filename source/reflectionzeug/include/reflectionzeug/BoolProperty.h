
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
    template <typename... Arguments>
    BoolProperty(Arguments&&... args);

    REFLECTIONZEUG_API virtual std::string toString() const;
    REFLECTIONZEUG_API virtual bool fromString(const std::string & string);

    REFLECTIONZEUG_API void toggleValue();

};

} // namespace reflectionzeug

#include <reflectionzeug/BoolProperty.hpp>
