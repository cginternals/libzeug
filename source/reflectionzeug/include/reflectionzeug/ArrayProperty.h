#pragma once

#include <type_traits>
#include <array>
#include <functional>

#include <signalzeug/Signal.h>

#include <reflectionzeug/property_declaration.h>
#include <reflectionzeug/AbstractPropertyCollection.h>
#include <reflectionzeug/AbstractValueProperty.h>

namespace reflectionzeug
{

/**
 * \brief Property implementation that stores an std::array.
 *
 * It can either store the value itself or access it through
 * element-based getter and setter.
 * It uses the property implementations of the single value properties,
 * therefore any single value type is also supported as the element type in arrays.
 *
 * \ingroup property_hierarchy
 */
template <typename Type, size_t Size>
class ArrayProperty : public AbstractPropertyCollection, public AbstractValueProperty
{
    static_assert(Size > 0, "Size must be greater than zero");

public:
    static size_t stype();

public:
    ArrayProperty();
    virtual ~ArrayProperty() = 0;

	virtual bool isCollection() const;
	virtual bool isValue() const;

    virtual size_t type() const;

    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);

    virtual Variant toVariant() const;
    virtual bool fromVariant(const Variant & variant);

    virtual Property<Type> * at(size_t i);
    virtual const Property<Type> * at(size_t i) const;

    virtual bool isEmpty() const;
    virtual size_t count() const;
    virtual int indexOf(const AbstractProperty * property) const;

    std::array<Type, Size> value() const;
    void setValue(const std::array<Type, Size> & array);

    Type element(size_t i) const;
    void setElement(size_t i, const Type & value);

    virtual void forEach(const std::function<void(AbstractProperty &)> & functor);
    virtual void forEach(const std::function<void(const AbstractProperty &)> & functor) const;

    void forEach(const std::function<void(Property<Type> &)> & functor);
    void forEach(const std::function<void(const Property<Type> &)> & functor) const;

    signalzeug::Signal<const std::array<Type, Size> &> valueChanged;

protected:
    void setAccessors(const std::function<Type (size_t)> & getter,
                      const std::function<void(size_t, const Type &)> & setter);

    template <class Object>
    void setAccessors(Object * object,
                      const Type & (Object::*getter_pointer)(size_t) const,
                      void (Object::*setter_pointer)(size_t, const Type &));

    template <class Object>
    void setAccessors(Object * object,
                      Type (Object::*getter_pointer)(size_t) const,
                      void (Object::*setter_pointer)(size_t, const Type &));

    template <class Object>
    void setAccessors(Object * object,
                      Type (Object::*getter_pointer)(size_t) const,
                      void (Object::*setter_pointer)(size_t, Type));
private:
    std::function<Type (size_t)> m_getter;
    std::function<void(size_t, const Type &)> m_setter;
    std::array<Property<Type> *, Size> m_properties;
};

} // namespace reflectionzeug

#include <reflectionzeug/ArrayProperty.hpp>

