
#pragma once


#include <memory>
#include <functional>
#include <array>

#include <reflectionzeug/type/AbstractPropertyValue.h>
#include <reflectionzeug/type/AbstractCollection.h>
#include <reflectionzeug/type/ArrayAccessor.h>


namespace reflectionzeug
{


template <typename Type>
class Property;


/**
*  @brief
*    Base class for typed arrays (read/write)
*/
template <typename Type, size_t Size>
class AbstractPropertyArray : public AbstractPropertyValue<std::array<Type, Size>>
                            , public AbstractCollection
{
public:
    AbstractPropertyArray(const std::string & name);

    AbstractPropertyArray(const std::string & name, const std::array<Type, Size> & value);

    AbstractPropertyArray(const std::string & name,
          std::function<Type (size_t)> getter,
          std::function<void(size_t, const Type &)> setter);

    template <class Object>
    AbstractPropertyArray(const std::string & name, Object * object,
          const Type & (Object::*getter_pointer)(size_t) const,
          void (Object::*setter_pointer)(size_t, const Type &));

    template <class Object>
    AbstractPropertyArray(const std::string & name, Object * object,
          Type (Object::*getter_pointer)(size_t) const,
          void (Object::*setter_pointer)(size_t, const Type &));

    template <class Object>
    AbstractPropertyArray(const std::string & name, Object * object,
          Type (Object::*getter_pointer)(size_t) const,
          void (Object::*setter_pointer)(size_t, Type));

    AbstractPropertyArray(const std::string & name, ArrayAccessor<Type, Size> * accessor);

    virtual ~AbstractPropertyArray();

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
class AbstractPropertyArray<const Type, Size> : public AbstractPropertyArray<Type, Size>
{
public:
    AbstractPropertyArray(const std::string & name);

    AbstractPropertyArray(const std::string & name, const std::array<Type, Size> & value);

    AbstractPropertyArray(const std::string & name, std::function<Type (size_t)> getter);

    template <class Object>
    AbstractPropertyArray(const std::string & name, Object * object,
          const Type & (Object::*getter_pointer)(size_t) const);

    template <class Object>
    AbstractPropertyArray(const std::string & name, Object * object,
          Type (Object::*getter_pointer)(size_t) const);

    AbstractPropertyArray(const std::string & name, ArrayAccessor<const Type, Size> * accessor);

    virtual ~AbstractPropertyArray();
};


} // namespace reflectionzeug


#include <reflectionzeug/type/AbstractPropertyArray.hpp>
