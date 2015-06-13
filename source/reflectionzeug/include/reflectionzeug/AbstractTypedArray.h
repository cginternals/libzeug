
#pragma once


#include <memory>
#include <functional>
#include <array>

#include <reflectionzeug/AbstractTyped.h>
#include <reflectionzeug/AbstractCollection.h>
#include <reflectionzeug/ArrayAccessor.h>


namespace reflectionzeug
{


template <typename Type>
class Typed;


/**
*  @brief
*    Base class for typed arrays (read/write)
*/
template <typename Type, size_t Size>
class AbstractTypedArray : public AbstractTyped<std::array<Type, Size>>
                         , public AbstractCollection
{
public:
    AbstractTypedArray();

    AbstractTypedArray(const std::array<Type, Size> & value);

    AbstractTypedArray(std::function<Type (size_t)> getter,
          std::function<void(size_t, const Type &)> setter);

    template <class Object>
    AbstractTypedArray(Object * object,
          const Type & (Object::*getter_pointer)(size_t) const,
          void (Object::*setter_pointer)(size_t, const Type &));

    template <class Object>
    AbstractTypedArray(Object * object,
          Type (Object::*getter_pointer)(size_t) const,
          void (Object::*setter_pointer)(size_t, const Type &));

    template <class Object>
    AbstractTypedArray(Object * object,
          Type (Object::*getter_pointer)(size_t) const,
          void (Object::*setter_pointer)(size_t, Type));

    AbstractTypedArray(ArrayAccessor<Type, Size> * accessor);

    virtual ~AbstractTypedArray();

    virtual bool isEmpty() const override;
    virtual size_t count() const override;

    virtual AbstractValue * at(size_t i) override;
    virtual const AbstractValue * at(size_t i) const override;

    virtual int indexOf(const AbstractValue * value) const override;

    virtual void forEach(const std::function<void(AbstractValue &)> & callback) override;
    virtual void forEach(const std::function<void(const AbstractValue &)> & callback) const override;

    Type getElement(size_t i) const;
    void setElement(size_t i, const Type & value);


protected:
  void init();


protected:
    ArrayAccessor<Type, Size>     * m_arrayAccessor;
    std::array<Typed<Type> *, Size> m_elements;
};


/**
*  @brief
*    Base class for typed arrays (read-only)
*/
template <typename Type, size_t Size>
class AbstractTypedArray<const Type, Size> : public AbstractTypedArray<Type, Size>
{
public:
    AbstractTypedArray();

    AbstractTypedArray(const std::array<Type, Size> & value);

    AbstractTypedArray(std::function<Type (size_t)> getter);

    template <class Object>
    AbstractTypedArray(Object * object,
          const Type & (Object::*getter_pointer)(size_t) const);

    template <class Object>
    AbstractTypedArray(Object * object,
          Type (Object::*getter_pointer)(size_t) const);

    AbstractTypedArray(ArrayAccessor<const Type, Size> * accessor);

    virtual ~AbstractTypedArray();
};


} // namespace reflectionzeug


#include <reflectionzeug/AbstractTypedArray.hpp>
