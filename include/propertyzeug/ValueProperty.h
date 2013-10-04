
#pragma once

#include <memory>

#include "AbstractProperty.h"
#include "StoredValue.h"
#include "AccessorValue.h"

namespace zeug {
    
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
    
    signalzeug::Signal<const Type &> valueChanged;
protected:
    std::unique_ptr<AbstractValue<Type>> m_value;
};

} // namespace

#include "ValueProperty.hpp"
