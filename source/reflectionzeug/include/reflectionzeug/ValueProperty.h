
#pragma once

#include <memory>

#include <signalzeug/Signal.h>

#include <reflectionzeug/reflectionzeug.h>
#include <reflectionzeug/ValuePropertyInterface.h>
#include <reflectionzeug/StoredValue.h>
#include <reflectionzeug/AccessorValue.h>

namespace reflectionzeug
{

/** \brief Part of the property hierarchy. The Template Class for all properties that have a value.
 */
template <typename Type>
class ValueProperty : public virtual ValuePropertyInterface
{
public:
    static size_t stype();

public:
    ValueProperty(const Type & value);
    
    ValueProperty(const std::function<Type()> & getter,
                  const std::function<void(const Type &)> & setter);
    
    template <class Object>
    ValueProperty(Object & object, 
                  const Type & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const Type &));
    
    template <class Object>
    ValueProperty(Object & object, 
                  Type (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const Type &));
    
    template <class Object>
    ValueProperty(Object & object, 
                  Type (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(Type));
    
    virtual ~ValueProperty() = 0;

    virtual Type value() const;
    virtual void setValue(const Type & value);

    virtual void accept(AbstractPropertyVisitor * visitor, bool warn = true);

    virtual size_t type();
    
    signalzeug::Signal<const Type &> valueChanged;

protected:
    std::unique_ptr<AbstractValue<Type>> m_value;
};

} // namespace reflectionzeug

#include "ValueProperty.hpp"
