
#pragma once


#include <memory>
#include <functional>

#include <reflectionzeug/property/AbstractProperty.h>
#include <reflectionzeug/property/Accessor.h>


namespace reflectionzeug
{


/**
*  @brief
*    Base class for typed values (read/write)
*/
template <typename Type>
class AbstractValueProperty : public AbstractProperty
{
public:
    signalzeug::Signal<const Type &> valueChanged;  /**< Called when the value has been changed */


public:
    AbstractValueProperty(const std::string & name = "");

    AbstractValueProperty(const std::string & name, const Type & value);

    AbstractValueProperty(const std::string & name,
          std::function<Type ()> getter,
          std::function<void(const Type &)> setter);

    template <class Object>
    AbstractValueProperty(const std::string & name, Object * object,
          const Type & (Object::*getter_pointer)() const,
          void (Object::*setter_pointer)(const Type &));

    template <class Object>
    AbstractValueProperty(const std::string & name, Object * object,
          Type (Object::*getter_pointer)() const,
          void (Object::*setter_pointer)(const Type &));

    template <class Object>
    AbstractValueProperty(const std::string & name, Object * object,
          Type (Object::*getter_pointer)() const,
          void (Object::*setter_pointer)(Type));

    AbstractValueProperty(const std::string & name, Accessor<Type> * accessor);

    virtual ~AbstractValueProperty();

    virtual const std::type_info & type() const override;

    virtual Variant toVariant() const override;
    virtual bool fromVariant(const Variant & value) override;

    Type value() const;
    void setValue(const Type & value);


protected:
    std::unique_ptr<Accessor<Type>> m_accessor;
};


/**
*  @brief
*    Base class for typed values (read-only)
*/
template <typename Type>
class AbstractValueProperty<const Type> : public AbstractValueProperty<Type>
{
public:
    AbstractValueProperty(const std::string & name = "");

    AbstractValueProperty(const std::string & name, const Type & value);

    AbstractValueProperty(const std::string & name, std::function<Type ()> getter);

    template <class Object>
    AbstractValueProperty(const std::string & name, Object * object,
          const Type & (Object::*getter_pointer)() const);

    template <class Object>
    AbstractValueProperty(const std::string & name, Object * object,
          Type (Object::*getter_pointer)() const);

    AbstractValueProperty(const std::string & name, Accessor<const Type> * accessor);

    virtual ~AbstractValueProperty();
};


} // namespace reflectionzeug


#include <reflectionzeug/property/AbstractValueProperty.hpp>
