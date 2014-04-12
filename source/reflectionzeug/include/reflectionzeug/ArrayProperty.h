
#pragma once

#include <type_traits>
#include <memory>
#include <array>
#include <functional>

#include <reflectionzeug/property_declaration.h>
#include <reflectionzeug/ArrayPropertyInterface.h>

namespace reflectionzeug
{
    
template <typename, size_t>
class AbstractArrayValue;
    
/** \brief Part of the Property Hierarchy that manages properties while being a property itself.
*/
template <typename Type, size_t Size>
class ArrayProperty : public ArrayPropertyInterface
{
    static_assert(Size > 0, "Size must be greater than zero");

public:
    static size_t stype();

public:
    ArrayProperty(const std::string & name, const std::array<Type, Size> & array);

    ArrayProperty(const std::string & name,
                  const std::function<Type (size_t)> & getter,
                  const std::function<void(size_t, const Type &)> & setter);
    
    template <class Object>
    ArrayProperty(const std::string & name,
                  Object & object, 
                  const Type & (Object::*getter_pointer)(size_t) const,
                  void (Object::*setter_pointer)(size_t, const Type &));
    
    template <class Object>
    ArrayProperty(const std::string & name,
                  Object & object, 
                  Type (Object::*getter_pointer)(size_t) const,
                  void (Object::*setter_pointer)(size_t, const Type &));
    
    template <class Object>
    ArrayProperty(const std::string & name,
                  Object & object, 
                  Type (Object::*getter_pointer)(size_t) const,
                  void (Object::*setter_pointer)(size_t, Type));

    ~ArrayProperty();

    virtual void accept(AbstractPropertyVisitor * visitor, bool warn);

    virtual size_t type();

    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);

    std::array<Type, Size> array() const;
    void setArray(const std::array<Type, Size> & array);

    Type value(size_t i) const;
    void setValue(size_t i, const Type & value);

    size_t size() const;

    Property<Type> * at(size_t i);
    const Property<Type> * at(size_t i) const;

    const std::array<Property<Type> *, Size> & subProperties();
    const std::array<const Property<Type> *, Size> & subProperties() const;

private:
    void init();

private:
    std::unique_ptr<AbstractArrayValue<Type, Size>> m_array;
    std::array<Property<Type> *, Size> m_properties;

};

} // namespace reflectionzeug

#include "ArrayProperty.hpp"

