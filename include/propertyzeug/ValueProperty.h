
#pragma once

#include <memory>

#include <signalzeug/Signal.h>

#include <propertyzeug/propertyzeug.h>
#include <propertyzeug/ValuePropertyBase.h>
#include <propertyzeug/StoredValue.h>
#include <propertyzeug/AccessorValue.h>

namespace zeug {
    
/** @brief
 * Part of the property hierarchy.
 * The Template Class for all properties that have a value.
 */

template <typename Type>
class ValueProperty : public ValuePropertyBase
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
    
    Signal<const Type &> valueChanged;
protected:
    std::unique_ptr<AbstractValue<Type>> m_value;
};

} // namespace zeug

#include "ValueProperty.hpp"
