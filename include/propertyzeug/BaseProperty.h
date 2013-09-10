
#pragma once

#include "AbstractProperty.h"
#include "StoredValue.h"
#include "AccessorValue.h"

namespace propertyzeug {
    
/** @brief
 * Part of the property hierarchy.
 * The super class of all properties that have a value.
 */

template <typename Type>
class PROPERTYZEUG_API BaseProperty : public AbstractProperty
{
public:
    BaseProperty(const std::string & name, const Type & value);
    
    BaseProperty(const std::string & name, 
                 const std::function<const Type & ()> & getter,
                 const std::function<void(const Type &)> & setter);
    
    template <class Object>
    BaseProperty(const std::string & name,
                 Object & object, const Type & (Object::*getter_pointer)() const,
                 void (Object::*setter_pointer)(const Type &));
    
    template <class Object>
    BaseProperty(const std::string & name,
                 Object & object, Type (Object::*getter_pointer)() const,
                 void (Object::*setter_pointer)(const Type &));
    
    virtual ~BaseProperty();

    virtual const Type & value() const;
    virtual void setValue(const Type & value);
    
protected:
    std::unique_ptr<AbstractValue<Type>> m_value;
};

template <typename Type>
BaseProperty<Type>::BaseProperty(const std::string & name,
    const Type & value)
:   AbstractProperty(name)
,   m_value(new StoredValue<Type>(value))
{
}

template <typename Type>
BaseProperty<Type>::BaseProperty(const std::string & name, 
    const std::function<const Type & ()> & getter,
    const std::function<void(const Type &)> & setter)
:   AbstractProperty(name)
,   m_value(new AccessorValue<Type>(getter, setter))
{
}

template <typename Type>
template <class Object>
BaseProperty<Type>::BaseProperty(const std::string & name,
    Object & object, const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   AbstractProperty(name)
,   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
}
    
template <typename Type>
template <class Object>
BaseProperty<Type>::BaseProperty(const std::string & name,
    Object & object, Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
:   AbstractProperty(name)
,   m_value(new AccessorValue<Type>(object, getter_pointer, setter_pointer))
{
}

template <typename Type>
BaseProperty<Type>::~BaseProperty()
{
}

template <typename Type>
const Type & BaseProperty<Type>::value() const
{
    return m_value->get();
}

template <typename Type>
void BaseProperty<Type>::setValue(const Type & value)
{
    m_value->set(value);
    m_announcer.notify(events::kValueChanged);
}

} // namespace
