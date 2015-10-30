
#pragma once


#include <functional>

#include <reflectionzeug/property/ArrayAccessor.h>


namespace reflectionzeug
{


/**
*  @brief
*    Accessor (read/write) via getter/setter functions
*/
template <typename Type, size_t Size>
class ArrayAccessorGetSet : public ArrayAccessor<Type, Size>
{
    static_assert(Size > 0, "Size has to be greater than 0");
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] getter
    *    Function to get an element of the array
    *  @param[in] setter
    *    Function to set an element of the array
    */
    ArrayAccessorGetSet(const std::function<Type (size_t)> & getter,
                        const std::function<void(size_t, const Type &)> & setter);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Function to get an element of the array
    *  @param[in] setter
    *    Function to set an element of the array
    */
    template <class Object>
    ArrayAccessorGetSet(Object * object,
                        const Type & (Object::*getter_pointer)(size_t) const,
                        void (Object::*setter_pointer)(size_t, const Type &));

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Function to get an element of the array
    *  @param[in] setter
    *    Function to set an element of the array
    */
    template <class Object>
    ArrayAccessorGetSet(Object * object,
                        Type (Object::*getter_pointer)(size_t) const,
                        void (Object::*setter_pointer)(size_t, const Type &));

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Function to get an element of the array
    *  @param[in] setter
    *    Function to set an element of the array
    */
    template <class Object>
    ArrayAccessorGetSet(Object * object,
                       Type (Object::*getter_pointer)(size_t) const,
                       void (Object::*setter_pointer)(size_t, Type));

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ArrayAccessorGetSet();

    // Virtual AbstractAccessor interface
    virtual AbstractAccessor * clone() const override;

    // Virtual Accessor<Type> interface
    virtual std::array<Type, Size> * ptr() const override;
    virtual std::array<Type, Size> value() const override;
    virtual void setValue(const std::array<Type, Size> & array) override;

    // Virtual ArrayAccessor<Type, Size> interface
    virtual Type getElement(size_t i) const override;
    virtual void setElement(size_t i, const Type & value) override;


protected:
    std::function<Type (size_t)>              m_getter; ///< Function to get an element of the array
    std::function<void(size_t, const Type &)> m_setter; ///< Function to set an element of the array
};


/**
*  @brief
*    Accessor (read-only) via getter/setter functions
*/
template <typename Type, size_t Size>
class ArrayAccessorGetSet<const Type, Size> : public ArrayAccessor<const Type, Size>
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] getter
    *    Function to get an element of the array
    */
    ArrayAccessorGetSet(const std::function<Type (size_t)> & getter);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Function to get an element of the array
    */
    template <class Object>
    ArrayAccessorGetSet(Object * object,
                        const Type & (Object::*getter_pointer)(size_t) const);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Function to get an element of the array
    */
    template <class Object>
    ArrayAccessorGetSet(Object * object,
                        Type (Object::*getter_pointer)(size_t) const);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ArrayAccessorGetSet();

    // Virtual AbstractAccessor interface
    virtual AbstractAccessor * clone() const override;

    // Virtual Accessor<Type> interface
    virtual std::array<Type, Size> * ptr() const override;
    virtual std::array<Type, Size> value() const override;

    // Virtual ArrayAccessor<Type, Size> interface
    virtual Type getElement(size_t i) const override;


protected:
    std::function<Type (size_t)> m_getter; ///< Function to get an element of the array
};


} // namespace reflectionzeug


#include <reflectionzeug/property/ArrayAccessorGetSet.hpp>
