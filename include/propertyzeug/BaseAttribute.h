
#pragma once

#include "AbstractAttribute.h"
#include "StoredValue.h"
#include "AccessorValue.h"

namespace propertyzeug {

template <typename Type>
class PROPERTYZEUG_API BaseAttribute : public AbstractAttribute
{
public:
    enum Events { kTitleChanged, kValueChanged };
    
    BaseAttribute(std::string name, std::string title, Type value);
    BaseAttribute(std::string name, std::string title, 
        std::function<Type()> getter, std::function<void(Type &)> setter);
    virtual ~BaseAttribute();

    Type value() const;
    void setValue(Type value);
protected:
    ValueInterface<Type> * m_value;
};

template <typename Type>
BaseAttribute<Type>::BaseAttribute(std::string name, std::string title, Type value)
:   AbstractAttribute(name, title)
,   m_value(new StoredValue<Type>(value))
{
}

template <typename Type>
BaseAttribute<Type>::BaseAttribute(std::string name, std::string title, 
    std::function<Type()> getter, std::function<void(Type &)> setter)
:   AbstractAttribute(name, title)
,   m_value(new AccessorValue<Type>(getter, setter))
{
}

template <typename Type>
BaseAttribute<Type>::~BaseAttribute()
{
    delete m_value;
}


template <typename Type>
Type BaseAttribute<Type>::value() const
{
    return m_value->get();
}

template <typename Type>
void BaseAttribute<Type>::setValue(Type value)
{
    m_value->set(value);
    m_announcer->notify(kValueChanged);
}

} // namespace