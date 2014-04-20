
#pragma once

#include <type_traits>
#include <memory>
#include <array>
#include <functional>

#include <reflectionzeug/property_declaration.h>
#include <reflectionzeug/AbstractPropertyCollection.h>
#include <reflectionzeug/AbstractValueProperty.h>

namespace reflectionzeug
{
    
template <typename, size_t>
class AbstractArrayValue;

template <typename Type, size_t Size>
class ArrayProperty : public AbstractPropertyCollection, public AbstractValueProperty
{
    static_assert(Size > 0, "Size must be greater than zero");

public:
    static size_t stype();

public:
    ArrayProperty(const std::array<Type, Size> & array);

    ArrayProperty(const std::function<Type (size_t)> & getter,
                  const std::function<void(size_t, const Type &)> & setter);
    
    template <class Object>
    ArrayProperty(Object & object, 
                  const Type & (Object::*getter_pointer)(size_t) const,
                  void (Object::*setter_pointer)(size_t, const Type &));
    
    template <class Object>
    ArrayProperty(Object & object, 
                  Type (Object::*getter_pointer)(size_t) const,
                  void (Object::*setter_pointer)(size_t, const Type &));
    
    template <class Object>
    ArrayProperty(Object & object, 
                  Type (Object::*getter_pointer)(size_t) const,
                  void (Object::*setter_pointer)(size_t, Type));

    virtual ~ArrayProperty() = 0;

    virtual void accept(AbstractPropertyVisitor * visitor);

    virtual size_t type() const;

    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);

    virtual Property<Type> * at(size_t i);
    virtual const Property<Type> * at(size_t i) const;
    
    virtual bool isEmpty() const;
    virtual size_t count() const;
    virtual int indexOf(const AbstractProperty * property) const;

    std::array<Type, Size> array() const;
    void setArray(const std::array<Type, Size> & array);

    Type value(size_t i) const;
    void setValue(size_t i, const Type & value);

    void forEach(const std::function<void(Property<Type> &)> & functor);
    void forEach(const std::function<void(const Property<Type> &)> & functor) const;

private:
    void init();

private:
    std::unique_ptr<AbstractArrayValue<Type, Size>> m_array;
    std::array<Property<Type> *, Size> m_properties;

};

} // namespace reflectionzeug

#include "ArrayProperty.hpp"

