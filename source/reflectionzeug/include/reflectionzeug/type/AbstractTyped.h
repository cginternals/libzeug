
#pragma once


#include <memory>
#include <functional>

#include <reflectionzeug/type/AbstractValue.h>
#include <reflectionzeug/type/Accessor.h>


namespace reflectionzeug
{


/**
*  @brief
*    Base class for typed values (read/write)
*/
template <typename Type>
class AbstractTyped : public AbstractValue
{
public:
    signalzeug::Signal<const Type &> valueChanged;  /**< Called when the value has been changed */


public:
    AbstractTyped(const std::string & name = "");

    AbstractTyped(const std::string & name, const Type & value);

    AbstractTyped(const std::string & name,
          std::function<Type ()> getter,
          std::function<void(const Type &)> setter);

    template <class Object>
    AbstractTyped(const std::string & name, Object * object,
          const Type & (Object::*getter_pointer)() const,
          void (Object::*setter_pointer)(const Type &));

    template <class Object>
    AbstractTyped(const std::string & name, Object * object,
          Type (Object::*getter_pointer)() const,
          void (Object::*setter_pointer)(const Type &));

    template <class Object>
    AbstractTyped(const std::string & name, Object * object,
          Type (Object::*getter_pointer)() const,
          void (Object::*setter_pointer)(Type));

    AbstractTyped(const std::string & name, Accessor<Type> * accessor);

    virtual ~AbstractTyped();

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
class AbstractTyped<const Type> : public AbstractTyped<Type>
{
public:
    AbstractTyped(const std::string & name = "");

    AbstractTyped(const std::string & name, const Type & value);

    AbstractTyped(const std::string & name, std::function<Type ()> getter);

    template <class Object>
    AbstractTyped(const std::string & name, Object * object,
          const Type & (Object::*getter_pointer)() const);

    template <class Object>
    AbstractTyped(const std::string & name, Object * object,
          Type (Object::*getter_pointer)() const);

    AbstractTyped(const std::string & name, Accessor<const Type> * accessor);

    virtual ~AbstractTyped();
};


} // namespace reflectionzeug


#include <reflectionzeug/type/AbstractTyped.hpp>
