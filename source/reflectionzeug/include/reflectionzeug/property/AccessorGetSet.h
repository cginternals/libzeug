
#pragma once


#include <functional>

#include <reflectionzeug/property/Accessor.h>


namespace reflectionzeug
{


/**
*  @brief
*    Accessor (read/write) via getter/setter functions
*/
template <typename Type>
class AccessorGetSet : public Accessor<Type>
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] getter
    *    Function to get the value
    *  @param[in] setter
    *    Function to set the value
    */
    AccessorGetSet(std::function<Type ()> getter,
                   std::function<void(const Type &)> setter);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Method to get the value
    *  @param[in] setter
    *    Method to set the value
    */
    template <class Object>
    AccessorGetSet(Object * object,
                   const Type & (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(const Type &));

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Method to get the value
    *  @param[in] setter
    *    Method to set the value
    */
    template <class Object>
    AccessorGetSet(Object * object,
                   Type (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(const Type &));

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Method to get the value
    *  @param[in] setter
    *    Method to set the value
    */
    template <class Object>
    AccessorGetSet(Object * object,
                   Type (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(Type));

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AccessorGetSet();

    // Virtual AbstractAccessor interface
    virtual AbstractAccessor * clone() const override;

    // Virtual Accessor<Type> interface
    virtual Type * ptr() const override;
    virtual Type value() const override;
    virtual void setValue(const Type & value) override;


protected:
    std::function<Type ()>            m_getter; ///< Function to get the value
    std::function<void(const Type &)> m_setter; ///< Function to set the value
};


/**
*  @brief
*    Accessor (read-only) via getter/setter functions
*/
template <typename Type>
class AccessorGetSet<const Type> : public Accessor<const Type>
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] getter
    *    Function to get the value
    */
    AccessorGetSet(std::function<Type ()> getter);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Function to get the value
    */
    template <class Object>
    AccessorGetSet(Object * object,
                   const Type & (Object::*getter_pointer)() const);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Function to get the value
    */
    template <class Object>
    AccessorGetSet(Object * object,
                   Type (Object::*getter_pointer)() const);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AccessorGetSet();

    // Virtual AbstractAccessor interface
    virtual AbstractAccessor * clone() const override;

    // Virtual Accessor<Type> interface
    virtual Type * ptr() const override;
    virtual Type value() const override;


protected:
    std::function<Type ()> m_getter; ///< Function to get the value
};


} // namespace reflectionzeug


#include <reflectionzeug/property/AccessorGetSet.hpp>
