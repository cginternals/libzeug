
#pragma once

#include <memory>
#include "AbstractProperty.h"
#include "StoredValue.h"
#include "AccessorValue.h"

namespace propertyzeug {
    
/** @brief
 * Part of the property hierarchy.
 * The super class of all properties that have a value.
 */

template <typename Type>
class PROPERTYZEUG_API ValueProperty : public AbstractProperty
{
public:
    ValueProperty(const std::string & name, const Type & value);
    
    ValueProperty(const std::string & name, 
                 const std::function<const Type & ()> & getter,
                 const std::function<void(const Type &)> & setter);
    
    template <class Object>
    ValueProperty(const std::string & name,
                 Object & object, const Type & (Object::*getter_pointer)() const,
                 void (Object::*setter_pointer)(const Type &));
    
    template <class Object>
    ValueProperty(const std::string & name,
                 Object & object, Type (Object::*getter_pointer)() const,
                 void (Object::*setter_pointer)(const Type &));
    
    virtual ~ValueProperty();

    virtual const Type & value() const;
    virtual void setValue(const Type & value);
    
protected:
    std::unique_ptr<AbstractValue<Type>> m_value;
};

template <typename Type>
ValueProperty<Type>::ValueProperty(const std::string & name,
    const Type & value)
:   AbstractProperty(name)
,   m_value(new StoredValue<Type>(value))
{
}

template <typename Type>
ValueProperty<Type>::ValueProperty(const std::string & name, 
    const std::function<const Type & ()> & getter,
    const std::function<void(const Type &)> & setter)
:   AbstractProperty(name)
,   m_value(new AccessorValue<Type>(getter, setter))
{
}

template <typename Type>
template <class Object>
ValueProperty<Type>::ValueProperty(const std::string & name,
    Object & object, const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   AbstractProperty(name)
,   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
}
    
template <typename Type>
template <class Object>
ValueProperty<Type>::ValueProperty(const std::string & name,
    Object & object, Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   AbstractProperty(name)
,   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
}

template <typename Type>
ValueProperty<Type>::~ValueProperty()
{
}

template <typename Type>
const Type & ValueProperty<Type>::value() const
{
    return m_value->get();
}

template <typename Type>
void ValueProperty<Type>::setValue(const Type & value)
{
    m_value->set(value);
    m_announcer.notify(events::kValueChanged);
}

} // namespace
