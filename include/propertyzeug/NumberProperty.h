
#pragma once

#include <sstream>
#include "BaseProperty.h"

namespace propertyzeug {
    
/** @brief
 * Part of the property hierarchy.
 * Extends the BaseProperty by adding a minimum and maximum.
 */

template <typename Type>
class PROPERTYZEUG_API NumberProperty : public BaseProperty<Type>
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
    
    virtual std::string valueAsString() const;
    
protected:
    Type m_min;
    Type m_max;
};

template <typename Type>
NumberProperty<Type>::NumberProperty(const std::string & name, const Type & value)
:   BaseProperty<Type>(name, value)
,   m_min(0)
,   m_max(0)
{
};

template <typename Type>
NumberProperty<Type>::NumberProperty(const std::string & name, 
    const std::function<const Type & ()> & getter,
    const std::function<void(const Type &)> & setter)
:   BaseProperty<Type>(name, getter, setter)
,   m_min(0)
,   m_max(0)
{
};

template <typename Type>
template <class Object>
NumberProperty<Type>::NumberProperty(const std::string & name,
    Object & object, const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   BaseProperty<Type>(name, object, getter_pointer, setter_pointer)
,   m_min(0)
,   m_max(0)
{
};

template <typename Type>
template <class Object>
NumberProperty<Type>::NumberProperty(const std::string & name,
    Object & object, Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
:   BaseProperty<Type>(name, object, getter_pointer, setter_pointer)
,   m_min(0)
,   m_max(0)
{
};

template <typename Type>
const Type & NumberProperty<Type>::minimum() const
{
    return m_min;
}

template <typename Type>
void NumberProperty<Type>::setMinimum(const Type & minimum)
{
    m_min = minimum;
    this->m_announcer.notify(events::kRangeChanged);
}


template <typename Type>
const Type & NumberProperty<Type>::maximum() const
{
    return m_max;
}

template <typename Type>
void NumberProperty<Type>::setMaximum(const Type & maximum)
{
    m_max = maximum;
    this->m_announcer.notify(events::kRangeChanged);
}
    
template <typename Type>
void NumberProperty<Type>::setRange(const Type & minimum, const Type & maximum)
{
    m_min = minimum;
    m_max = maximum;
    this->m_announcer.notify(events::kRangeChanged);
}
    
template <typename Type>
std::string NumberProperty<Type>::valueAsString() const
{
    std::stringstream stream;
    stream << this->value();
    return stream.str();
}

} // namespace
