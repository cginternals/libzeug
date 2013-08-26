
#pragma once

#include "BaseProperty.h"

namespace propertyzeug {
    
/** @brief
 * Part of the property hierarchy.
 * Extends the BaseProperty by adding a minimum and maximum.
 */

template <typename Type>
class PROPERTYZEUG_API LimitProperty : public BaseProperty<Type>
{
public:
    LimitProperty(const std::string & name, const std::string & title, const Type & value);

    LimitProperty(const std::string & name, const std::string & title, 
                  const std::function<const Type & ()> & getter,
                  const std::function<void(const Type &)> & setter);
    
    template <class Object>
    LimitProperty(const std::string & name, const std::string & title,
                  Object & object, const Type & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const Type &));
    
    template <class Object>
    LimitProperty(const std::string & name, const std::string & title,
                  Object & object, Type (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(Type));
    
    const Type & minimum() const;
    void setMinimum(const Type & minimum);

    const Type & maximum() const;
    void setMaximum(const Type & maximum);
    
protected:
    Type m_min;
    Type m_max;
};

template <typename Type>
LimitProperty<Type>::LimitProperty(const std::string & name, const std::string & title, const Type & value)
:   BaseProperty<Type>(name, title, value)
,   m_min(0)
,   m_max(0)
{
};

template <typename Type>
LimitProperty<Type>::LimitProperty(const std::string & name, const std::string & title, 
    const std::function<const Type & ()> & getter,
    const std::function<void(const Type &)> & setter)
:   BaseProperty<Type>(name, title, getter, setter)
,   m_min(0)
,   m_max(0)
{
};

template <typename Type>
template <class Object>
LimitProperty<Type>::LimitProperty(const std::string & name, const std::string & title,
    Object & object, const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   BaseProperty<Type>(name, title, object, getter_pointer, setter_pointer)
,   m_min(0)
,   m_max(0)
{
};

template <typename Type>
template <class Object>
LimitProperty<Type>::LimitProperty(const std::string & name, const std::string & title,
    Object & object, Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
:   BaseProperty<Type>(name, title, object, getter_pointer, setter_pointer)
,   m_min(0)
,   m_max(0)
{
};

template <typename Type>
const Type & LimitProperty<Type>::minimum() const
{
    return m_min;
}

template <typename Type>
void LimitProperty<Type>::setMinimum(const Type & minimum)
{
    m_min = minimum;
    this->m_announcer.notify(events::kLimitsChanged);
}


template <typename Type>
const Type & LimitProperty<Type>::maximum() const
{
    return m_max;
}

template <typename Type>
void LimitProperty<Type>::setMaximum(const Type & maximum)
{
    m_max = maximum;
    this->m_announcer.notify(events::kLimitsChanged);
}

} // namespace