
#pragma once


#include <memory>
#include <functional>
#include <array>

#include <reflectionzeug/property/AbstractValueProperty.h>
#include <reflectionzeug/property/AbstractCollection.h>
#include <reflectionzeug/property/ArrayAccessor.h>


namespace reflectionzeug
{


template <typename Type>
class Property;


/**
*  @brief
*    Base class for typed arrays (read/write)
*/
template <typename Type, size_t Size>
class AbstractArrayProperty : public AbstractValueProperty<std::array<Type, Size>>
                            , public AbstractCollection
{
public:
    AbstractArrayProperty(const std::string & name);

    AbstractArrayProperty(const std::string & name, const std::array<Type, Size> & value);

    AbstractArrayProperty(const std::string & name,
          std::function<Type (size_t)> getter,
          std::function<void(size_t, const Type &)> setter);

    template <class Object>
    AbstractArrayProperty(const std::string & name, Object * object,
          const Type & (Object::*getter_pointer)(size_t) const,
          void (Object::*setter_pointer)(size_t, const Type &));

    template <class Object>
    AbstractArrayProperty(const std::string & name, Object * object,
          Type (Object::*getter_pointer)(size_t) const,
          void (Object::*setter_pointer)(size_t, const Type &));

    template <class Object>
    AbstractArrayProperty(const std::string & name, Object * object,
          Type (Object::*getter_pointer)(size_t) const,
          void (Object::*setter_pointer)(size_t, Type));

    AbstractArrayProperty(const std::string & name, ArrayAccessor<Type, Size> * accessor);

    virtual ~AbstractArrayProperty();

    virtual bool isEmpty() const override;
    virtual size_t count() const override;

    virtual AbstractProperty * at(size_t i) override;
    virtual const AbstractProperty * at(size_t i) const override;

    virtual int indexOf(const AbstractProperty * prop) const override;

    virtual void forEach(const std::function<void(AbstractProperty &)> & callback) override;
    virtual void forEach(const std::function<void(const AbstractProperty &)> & callback) const override;

    Type getElement(size_t i) const;
    void setElement(size_t i, const Type & value);


protected:
  void init();


protected:
    ArrayAccessor<Type, Size>          * m_arrayAccessor;
    std::array<Property<Type> *, Size>   m_elements;
};


/**
*  @brief
*    Base class for typed arrays (read-only)
*/
template <typename Type, size_t Size>
class AbstractArrayProperty<const Type, Size> : public AbstractArrayProperty<Type, Size>
{
public:
    AbstractArrayProperty(const std::string & name);

    AbstractArrayProperty(const std::string & name, const std::array<Type, Size> & value);

    AbstractArrayProperty(const std::string & name, std::function<Type (size_t)> getter);

    template <class Object>
    AbstractArrayProperty(const std::string & name, Object * object,
          const Type & (Object::*getter_pointer)(size_t) const);

    template <class Object>
    AbstractArrayProperty(const std::string & name, Object * object,
          Type (Object::*getter_pointer)(size_t) const);

    AbstractArrayProperty(const std::string & name, ArrayAccessor<const Type, Size> * accessor);

    virtual ~AbstractArrayProperty();
};


} // namespace reflectionzeug


#include <reflectionzeug/property/AbstractArrayProperty.hpp>
