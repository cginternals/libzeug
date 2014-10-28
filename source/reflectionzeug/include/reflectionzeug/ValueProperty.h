#pragma once

#include <memory>

#include <signalzeug/Signal.h>

#include <reflectionzeug/reflectionzeug_api.h>
#include <reflectionzeug/AbstractValueProperty.h>

namespace reflectionzeug
{

template <typename>
class AbstractValue;

/** 
 * \brief The template class for all properties that have a value other than std::array.
 *
 * It can either store the value itself or access it through getter and setter.
 *
 * \see AbstractValue
 * \ingroup property_hierarchy
 */
template <typename Type>
class ValueProperty : public virtual AbstractValueProperty
{
public:
    static size_t stype();

public:
    ValueProperty(const Type & value);
    
    ValueProperty(const std::function<Type()> & getter,
                  const std::function<void(const Type &)> & setter);
    
    template <class Object>
    ValueProperty(Object * object, 
                  const Type & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const Type &));
    
    template <class Object>
    ValueProperty(Object * object, 
                  Type (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const Type &));
    
    template <class Object>
    ValueProperty(Object * object, 
                  Type (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(Type));
    
    virtual ~ValueProperty() = 0;

    virtual Type value() const;
    virtual void setValue(const Type & value);

    virtual size_t type() const;

    virtual Variant toVariant() const override;
    virtual bool fromVariant(const Variant & value) override;
    
    signalzeug::Signal<const Type &> valueChanged;

private:
    void init();

private:
    std::unique_ptr<AbstractValue<Type>> m_value;
};

} // namespace reflectionzeug

#include <reflectionzeug/ValueProperty.hpp>
