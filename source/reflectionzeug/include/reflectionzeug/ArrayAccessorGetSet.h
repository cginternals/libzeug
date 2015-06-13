
#pragma once


#include <functional>

#include <reflectionzeug/ArrayAccessor.h>


namespace reflectionzeug
{


/**
*  @brief
*    Accessor (read/write) via getter/setter functions
*/
template <typename Type, size_t Size>
class ArrayAccessorGetSet : public ArrayAccessor<Type, Size>
{
public:
    ArrayAccessorGetSet(const std::function<Type (size_t)> & getter,
                        const std::function<void(size_t, const Type &)> & setter);

    template <class Object>
    ArrayAccessorGetSet(Object * object,
                        const Type & (Object::*getter_pointer)(size_t) const,
                        void (Object::*setter_pointer)(size_t, const Type &));

    template <class Object>
    ArrayAccessorGetSet(Object * object,
                        Type (Object::*getter_pointer)(size_t) const,
                        void (Object::*setter_pointer)(size_t, const Type &));

    template <class Object>
    ArrayAccessorGetSet(Object * object,
                       Type (Object::*getter_pointer)(size_t) const,
                       void (Object::*setter_pointer)(size_t, Type));

    virtual ~ArrayAccessorGetSet();

    virtual std::array<Type, Size> getValue() const override;
    virtual void setValue(const std::array<Type, Size> & array) override;

    virtual Type getElement(size_t i) const override;
    virtual void setElement(size_t i, const Type & value) override;


protected:
    std::function<Type (size_t)>              m_getter;
    std::function<void(size_t, const Type &)> m_setter;
};


/**
*  @brief
*    Accessor (read-only) via getter/setter functions
*/
template <typename Type, size_t Size>
class ArrayAccessorGetSet<const Type, Size> : public ArrayAccessor<const Type, Size>
{
public:
    ArrayAccessorGetSet(const std::function<Type (size_t)> & getter);

    template <class Object>
    ArrayAccessorGetSet(Object * object,
                        const Type & (Object::*getter_pointer)(size_t) const);

    template <class Object>
    ArrayAccessorGetSet(Object * object,
                        Type (Object::*getter_pointer)(size_t) const);

    virtual ~ArrayAccessorGetSet();

    virtual std::array<Type, Size> getValue() const override;

    virtual Type getElement(size_t i) const override;


protected:
    std::function<Type (size_t)> m_getter;
};


} // namespace reflectionzeug


#include <reflectionzeug/ArrayAccessorGetSet.hpp>
