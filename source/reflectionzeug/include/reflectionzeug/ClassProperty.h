
#pragma once

#include <sstream>

#include <reflectionzeug/ValueProperty.h>

namespace reflectionzeug
{
    
/** \brief Part of the property hierarchy that extends the ValueProperty.
 */
template <typename Type>
class ClassProperty : public ValueProperty<Type>
{
public:
    template <typename... Arguments>
    ClassProperty(Arguments&&... args);

    virtual ~ClassProperty() = 0;
    
    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);

};

} // namespace reflectionzeug

#include "ClassProperty.hpp"
