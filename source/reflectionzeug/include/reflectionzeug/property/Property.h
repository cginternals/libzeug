
#pragma once


#include <reflectionzeug/base/template_helpers.h>
#include <reflectionzeug/property/PropertySignedIntegral.h>
#include <reflectionzeug/property/PropertyUnsignedIntegral.h>
#include <reflectionzeug/property/PropertyFloatingPoint.h>
#include <reflectionzeug/property/PropertyBool.h>
#include <reflectionzeug/property/PropertyString.h>
#include <reflectionzeug/property/PropertyColor.h>
#include <reflectionzeug/property/PropertyFilePath.h>
#include <reflectionzeug/property/PropertyArray.h>
#include <reflectionzeug/property/PropertyEnum.h>
#include <reflectionzeug/property/AbstractVisitor.h>


namespace reflectionzeug
{


/**
*  @brief
*    Class to throw compiler errors
*/
template <typename T>
class PropertyError;


/**
*  @brief
*    Class to recognize unsupported property types
*/
template <typename T>
class UnsupportedPropertyType : public AbstractTypedProperty<T>
{
public:
    /*
      If you got here from a compiler error, you have tried to instanciate
      a property for an unsupported type.

      Please create your own property extension class for the unsupported type
      by inheriting from AbstractTypedProperty<DataType> (and any matching
      abstract interfaces), and provide a specialization of
      PropertTypeSelector<DataType> with
          using Type = DataType;
    */
    PropertyError<T> error;


public:
    template <typename... Args>
    UnsupportedPropertyType(Args&&... /*args*/)
    {
    }

    virtual ~UnsupportedPropertyType()
    {
    }

    virtual std::string toString() const
    {
        return "";
    }

    virtual bool fromString(const std::string & /*string*/)
    {
        return false;
    }
};


/**
*  @brief
*    Helper class for selecting property types
*
*    Specialize this class template to register a new property type.
*    Define the property class that you want to use as typedef Type.
*/
template <typename T, typename = void>
struct PropertyTypeSelector
{
    using Type = UnsupportedPropertyType<T>;
};

/**
*  @brief
*    Property selector for properties of type bool
*/
template <>
struct PropertyTypeSelector<bool>
{
    using Type = PropertyBool;
};

/**
*  @brief
*    Property selector for properties of type Color
*/
template <>
struct PropertyTypeSelector<Color>
{
    using Type = PropertyColor;
};

/**
*  @brief
*    Property selector for properties of type std::string
*/
template <>
struct PropertyTypeSelector<std::string>
{
    using Type = PropertyString;
};

/**
*  @brief
*    Property selector for properties of type FilePath
*/
template <>
struct PropertyTypeSelector<FilePath>
{
    using Type = PropertyFilePath;
};

/**
*  @brief
*    Property selector for properties of integral types
*/
template <typename T>
struct PropertyTypeSelector<T, helper::EnableIf<helper::isSignedIntegral<T>>>
{
    using Type = PropertySignedIntegral<T>;
};

/**
*  @brief
*    Property selector for properties of unsigned integral types
*/
template <typename T>
struct PropertyTypeSelector<T, helper::EnableIf<helper::isUnsignedIntegral<T>>>
{
    using Type = PropertyUnsignedIntegral<T>;
};

/**
*  @brief
*    Property selector for properties of floating point types
*/
template <typename T>
struct PropertyTypeSelector<T, helper::EnableIf<helper::isFloatingPoint<T>>>
{
    using Type = PropertyFloatingPoint<T>;
};

/**
*  @brief
*    Property selector for properties of array types
*/
template <typename T>
struct PropertyTypeSelector<T, helper::EnableIf<helper::isArray<T>>>
{
    using Type = PropertyArray<typename T::value_type, std::tuple_size<T>::value>;
};

/**
*  @brief
*    Property selector for properties of enum types
*/
template <typename T>
struct PropertyTypeSelector<T, helper::EnableIf<std::is_enum<T>>>
{
    using Type = PropertyEnum<T>;
};

/**
*  @brief
*    Property to access a named value of a class or group
*
*    A property represents a named typed value that can represent,
*    e.g., a configuration option or a state of an object. Its
*    value resides outside of the property itself and is usually
*    accessed by defining getter and setter functions for the value.
*
*    Usually, properties should be created either inside a PropertyGroup
*    or inside an Object, and control the status of this object. 
*    Properties are an interface that can be used to automatically announce
*    and access values of an object, mainly for the purpose of user interaction.
*    This can be used to create automatic GUI interfaces and to provide
*    scripting interface for your classes.
*
*  @see propertyguizeug
*  @see scriptzeug
*/
template <typename T>
class Property : public PropertyTypeSelector<T>::Type
{
public:
    /**
    *  @brief
    *    Constructor
    */
    template <typename... Args>
    Property(Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Property();

    // Virtual AbstractProperty interface
    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/Property.hpp>
