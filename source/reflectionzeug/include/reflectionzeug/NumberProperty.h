#pragma once

#include <reflectionzeug/ValueProperty.h>

namespace reflectionzeug
{

/**
 * \brief An intermediate class for numeric property types.
 *
 * Two option are set in the constructor:
 * - minimum (Type): initialized to the lowest value of Type
 * - maximum (Type): initialized to the greates value of Type
 *
 * \ingroup property_hierarchy
 */
template <typename Type, typename SuperClass = AbstractValueProperty>
class NumberProperty : public ValueProperty<Type, SuperClass>
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

#include <reflectionzeug/NumberProperty.hpp>
