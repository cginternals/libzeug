
#pragma once


#include <reflectionzeug/property/AbstractPropertyValue.h>


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
template <typename Type>
class AbstractNumberProperty : public AbstractPropertyValue<Type>
{
public:
    template <typename... Args>
    AbstractNumberProperty(Args&&... args);
    virtual ~AbstractNumberProperty() = 0;

    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);


protected:
    virtual std::string matchRegex() const = 0;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/AbstractNumberProperty.hpp>
