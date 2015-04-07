
#pragma once


#include <memory>
#include <functional>

#include <reflectionzeug/new/ArrayAccessor.h>


namespace reflectionzeug
{


/**
*  @brief
*    Base class for typed arrays (read/write)
*/
template <typename Type, size_t Size>
class AbstractTypedArray
{
public:
    AbstractTypedArray();

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


protected:
    std::unique_ptr<ArrayAccessor<Type, Size>> m_accessor;
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


#include <reflectionzeug/new/AbstractTypedArray.hpp>
