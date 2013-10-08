
#pragma once

#include <sstream>

#include <propertyzeug/ValuePropertyTemplate.h>

namespace zeug 
{
    
/** @brief
 * Part of the property hierarchy.
 * Extends the ValuePropertyTemplate by adding a minimum and maximum.
 */

template <typename Type>
class NumberProperty : public ValuePropertyTemplate<Type>
{
public:
    NumberProperty(const std::string & name, const Type & value);

    NumberProperty(const std::string & name, 
                  const std::function<const Type & ()> & getter,
                  const std::function<void(const Type &)> & setter);
    
    template <class Object>
    NumberProperty(const std::string & name,
                  Object & object, const Type & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const Type &));
    
    template <class Object>
    NumberProperty(const std::string & name,
                  Object & object, Type (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(Type));
    
    const Type & minimum() const;
    void setMinimum(const Type & minimum);

    const Type & maximum() const;
    void setMaximum(const Type & maximum);
    
    void setRange(const Type & minimum, const Type & maximum);
    bool hasRanges() const;
    
    virtual std::string valueAsString() const;
    
protected:
    Type m_min;
    Type m_max;
};

} // namespace zeug

#include "NumberProperty.hpp"
