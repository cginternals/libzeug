
#pragma once

#include "AbstractAttribute.h"
#include "StoredValue.h"
#include "AccessorValue.h"

namespace propertyzeug {

template <typename Type>
class PROPERTYZEUG_API BaseAttribute : public AbstractAttribute
{
public:
    BaseAttribute(const std::string & name, const std::string & title, const Type & value);
    
    BaseAttribute(const std::string & name, const std::string & title, 
                  const std::function<const Type & ()> & getter,
                  const std::function<void(const Type &)> & setter);
    
    template <class Object>
    BaseAttribute(const std::string & name, const std::string & title,
                  Object & object, const Type & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const Type &));
    
    template <class Object>
    BaseAttribute(const std::string & name, const std::string & title,
                  Object & object, Type (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(Type));
    
    virtual ~BaseAttribute();

    const Type & value() const;
    void setValue(const Type & value);
protected:
    AbstractValue<Type> * m_value;
};

template <typename Type>
BaseAttribute<Type>::BaseAttribute(const std::string & name, const std::string & title,
    const Type & value)
:   AbstractAttribute(name, title)
,   m_value(new StoredValue<Type>(value))
{
}

template <typename Type>
BaseAttribute<Type>::BaseAttribute(const std::string & name, const std::string & title, 
    const std::function<const Type & ()> & getter,
    const std::function<void(const Type &)> & setter)
:   AbstractAttribute(name, title)
,   m_value(new AccessorValue<Type>(getter, setter))
{
}

template <typename Type>
template <class Object>
BaseAttribute<Type>::BaseAttribute(const std::string & name, const std::string & title,
    Object & object, const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   AbstractAttribute(name, title)
,   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
}
    
template <typename Type>
template <class Object>
BaseAttribute<Type>::BaseAttribute(const std::string & name, const std::string & title,
    Object & object, Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
:   AbstractAttribute(name, title)
,   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
}

template <typename Type>
BaseAttribute<Type>::~BaseAttribute()
{
    delete m_value;
}


template <typename Type>
const Type & BaseAttribute<Type>::value() const
{
    return m_value->get();
}

template <typename Type>
void BaseAttribute<Type>::setValue(const Type & value)
{
    m_value->set(value);
    m_announcer->notify(kValueChanged);
}

} // namespace