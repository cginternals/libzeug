
#pragma once


#include <memory>
#include <functional>

#include <reflectionzeug/property/AbstractValueProperty.h>
#include <reflectionzeug/property/Accessor.h>


namespace reflectionzeug
{


/**
*  @brief
*    Base class for typed properties (read/write)
*/
template <typename Type>
class AbstractTypedProperty : public AbstractValueProperty
{
public:
    signalzeug::Signal<const Type &> valueChanged;  ///< Called when the value has been changed


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] getter
    *    Function to get the value
    *  @param[in] setter
    *    Function to set the value
    */
    AbstractTypedProperty(const std::string & name,
          std::function<Type ()> getter,
          std::function<void(const Type &)> setter);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Method to get the value
    *  @param[in] setter
    *    Method to set the value
    */
    template <class Object>
    AbstractTypedProperty(const std::string & name, Object * object,
          const Type & (Object::*getter_pointer)() const,
          void (Object::*setter_pointer)(const Type &));

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Method to get the value
    *  @param[in] setter
    *    Method to set the value
    */
    template <class Object>
    AbstractTypedProperty(const std::string & name, Object * object,
          Type (Object::*getter_pointer)() const,
          void (Object::*setter_pointer)(const Type &));

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Method to get the value
    *  @param[in] setter
    *    Method to set the value
    */
    template <class Object>
    AbstractTypedProperty(const std::string & name, Object * object,
          Type (Object::*getter_pointer)() const,
          void (Object::*setter_pointer)(Type));

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] accessor
    *    Accessor to get/set the value
    */
    AbstractTypedProperty(const std::string & name, Accessor<Type> * accessor);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractTypedProperty();

    /**
    *  @brief
    *    Get property value
    *
    *  @return
    *    Value
    */
    Type value() const;

    /**
    *  @brief
    *    Set property value
    *
    *  @param[in] value
    *    Value
    */
    void setValue(const Type & value);

    // Virtual AbstractProperty interface
    virtual const std::type_info & type() const override;
    virtual Variant toVariant() const override;
    virtual bool fromVariant(const Variant & value) override;


protected:
    std::unique_ptr<Accessor<Type>> m_accessor; ///< Accessor to get/set the value
};


/**
*  @brief
*    Base class for typed properties (read-only)
*/
template <typename Type>
class AbstractTypedProperty<const Type> : public AbstractTypedProperty<Type>
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] getter
    *    Function to get the value
    */
    AbstractTypedProperty(const std::string & name, std::function<Type ()> getter);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Method to get the value
    */
    template <class Object>
    AbstractTypedProperty(const std::string & name, Object * object,
          const Type & (Object::*getter_pointer)() const);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] object
    *    Pointer to an object
    *  @param[in] getter
    *    Method to get the value
    */
    template <class Object>
    AbstractTypedProperty(const std::string & name, Object * object,
          Type (Object::*getter_pointer)() const);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] accessor
    *    Accessor to get/set the value
    */
    AbstractTypedProperty(const std::string & name, Accessor<const Type> * accessor);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractTypedProperty();
};


} // namespace reflectionzeug


#include <reflectionzeug/property/AbstractTypedProperty.hpp>
