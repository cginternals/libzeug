
#pragma once

#include <reflectionzeug/ValueProperty.h>

namespace reflectionzeug
{

/**
 * \brief An intermediate class for numeric property types.
 *
 * Adds a minimum and maximum as well as a step size.
 *
 * \ingroup property_hierarchy
 */
template <typename Type>
class NumberProperty : public ValueProperty<Type>
{
public:
    template <typename... Arguments>
    NumberProperty(Arguments&&... args);

    virtual ~NumberProperty() = 0;

    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);

protected:
    virtual std::string matchRegex() const = 0;

};

} // namespace reflectionzeug

#include "NumberProperty.hpp"
