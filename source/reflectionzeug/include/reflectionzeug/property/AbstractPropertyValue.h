
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
class AbstractPropertyValue : public AbstractProperty
{
public:
    signalzeug::Signal<const Type &> valueChanged;  /**< Called when the value has been changed */


public:
    AbstractPropertyValue(const std::string & name = "");

    AbstractPropertyValue(const std::string & name, const Type & value);

    AbstractPropertyValue(const std::string & name,
          std::function<Type ()> getter,
          std::function<void(const Type &)> setter);

    template <class Object>
    AbstractPropertyValue(const std::string & name, Object * object,
          const Type & (Object::*getter_pointer)() const,
          void (Object::*setter_pointer)(const Type &));

    template <class Object>
    AbstractPropertyValue(const std::string & name, Object * object,
          Type (Object::*getter_pointer)() const,
          void (Object::*setter_pointer)(const Type &));

    template <class Object>
    AbstractPropertyValue(const std::string & name, Object * object,
          Type (Object::*getter_pointer)() const,
          void (Object::*setter_pointer)(Type));

    AbstractPropertyValue(const std::string & name, Accessor<Type> * accessor);

    virtual ~AbstractPropertyValue();

    virtual const std::type_info & type() const override;

    virtual Variant toVariant() const override;
    virtual bool fromVariant(const Variant & value) override;

    Type * ptr() const;
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
class AbstractPropertyValue<const Type> : public AbstractPropertyValue<Type>
{
public:
    AbstractPropertyValue(const std::string & name = "");

    AbstractPropertyValue(const std::string & name, const Type & value);

    AbstractPropertyValue(const std::string & name, std::function<Type ()> getter);

    template <class Object>
    AbstractPropertyValue(const std::string & name, Object * object,
          const Type & (Object::*getter_pointer)() const);

    template <class Object>
    AbstractPropertyValue(const std::string & name, Object * object,
          Type (Object::*getter_pointer)() const);

    AbstractPropertyValue(const std::string & name, Accessor<const Type> * accessor);

    virtual ~AbstractPropertyValue();
};


} // namespace reflectionzeug


#include <reflectionzeug/property/AbstractPropertyValue.hpp>
