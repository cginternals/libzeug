
#pragma once

#include "BaseAttribute.h"

namespace propertyzeug {

template <typename Type>
class PROPERTYZEUG_API LimitAttribute : public BaseAttribute<Type>
{
public:
    LimitAttribute(const std::string & name, const std::string & title, const Type & value);

    LimitAttribute(const std::string & name, const std::string & title, 
                  const std::function<const Type & ()> & getter,
                  const std::function<void(const Type &)> & setter);
    
    template <class Object>
    LimitAttribute(const std::string & name, const std::string & title,
                  Object & object, const Type & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const Type &));
    
    template <class Object>
    LimitAttribute(const std::string & name, const std::string & title,
                  Object & object, Type (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(Type));
    
    const Type & minimum() const;
    void setMinimum(const Type & minimum) const;

    const Type & maximum() const;
    void setMaximum(const Type & maximum) const;
    
private:
    Type m_min;
    Type m_max;
};

template <typename Type>
LimitAttribute<Type>::LimitAttribute(const std::string & name, const std::string & title, const Type & value)
:   BaseAttribute<Type>(name, title, value)
,   m_min(0)
,   m_max(0)
{
};

template <typename Type>
LimitAttribute<Type>::LimitAttribute(const std::string & name, const std::string & title, 
    const std::function<const Type & ()> & getter,
    const std::function<void(const Type &)> & setter)
:   BaseAttribute<Type>(name, title, getter, setter)
,   m_min(0)
,   m_max(0)
{
};

template <typename Type>
template <class Object>
LimitAttribute<Type>::LimitAttribute(const std::string & name, const std::string & title,
    Object & object, const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   BaseAttribute<Type>(name, title, object, getter_pointer, setter_pointer)
,   m_min(0)
,   m_max(0)
{
};

template <typename Type>
template <class Object>
LimitAttribute<Type>::LimitAttribute(const std::string & name, const std::string & title,
    Object & object, Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
:   BaseAttribute<Type>(name, title, object, getter_pointer, setter_pointer)
,   m_min(0)
,   m_max(0)
{
};

template <typename Type>
const Type & LimitAttribute<Type>::minimum() const
{
    return m_min;
}

template <typename Type>
void LimitAttribute<Type>::setMinimum(const Type & minimum) const
{
    m_min = minimum;
}


template <typename Type>
const Type & LimitAttribute<Type>::maximum() const
{
    return m_max;
}

template <typename Type>
void LimitAttribute<Type>::setMaximum(const Type & maximum) const
{
    m_max = maximum;
}

} // namespace