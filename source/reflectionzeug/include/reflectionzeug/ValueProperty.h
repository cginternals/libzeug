#pragma once

#include <functional>
#include <type_traits>

#include <signalzeug/Signal.h>

#include <reflectionzeug/reflectionzeug_api.h>
#include <reflectionzeug/AbstractValueProperty.h>

namespace reflectionzeug
{

/**
 * \brief The template class for all properties that have a value other than std::array.
 *
 * It can either store the value itself or access it through getter and setter.
 *
 * \see AbstractValue
 * \ingroup property_hierarchy
 */
template <typename Type, typename SuperClass = AbstractValueProperty>
class ValueProperty : public SuperClass
{
    static_assert(std::is_base_of<AbstractValueProperty, SuperClass>::value,
                  "Super class must inherit from AbstractValueProperty");

public:
    static size_t stype();

public:
    ValueProperty();
    virtual ~ValueProperty() = 0;

    virtual Type value() const;
    virtual void setValue(const Type & value);

    virtual size_t type() const;

    virtual Variant toVariant() const override;
    virtual bool fromVariant(const Variant & value) override;

    signalzeug::Signal<const Type &> valueChanged;

protected:
    void setAccessors(const std::function<Type()> & getter,
                      const std::function<void(const Type &)> & setter);

    template <class Object>
    void setAccessors(Object * object,
                      const Type & (Object::*getter_pointer)() const,
                      void (Object::*setter_pointer)(const Type &));

    template <class Object>
    void setAccessors(Object * object,
                      Type (Object::*getter_pointer)() const,
                      void (Object::*setter_pointer)(const Type &));

    template <class Object>
    void setAccessors(Object * object,
                      Type (Object::*getter_pointer)() const,
                      void (Object::*setter_pointer)(Type));

private:
    std::function<Type ()> m_getter;
    std::function<void(const Type &)> m_setter;
};

} // namespace reflectionzeug

#include <reflectionzeug/ValueProperty.hpp>
