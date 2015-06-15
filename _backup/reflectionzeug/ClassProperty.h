#pragma once

#include <sstream>

#include <reflectionzeug/ValueProperty.h>

namespace reflectionzeug
{

/**
 * Provides a basic property implementation for classes that implement atleast
 * a copy constructor and the following interface:
 * \code{.cpp}
 * static Class fromString(std::string string, bool * ok);
 * std::string toString();
 * \endcode
 * \ingroup property_hierarchy
 */
template <typename Type>
class ClassProperty : public ValueProperty<Type>
{
public:
    virtual ~ClassProperty() = 0;

    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);
};

} // namespace reflectionzeug

#include <reflectionzeug/ClassProperty.hpp>
