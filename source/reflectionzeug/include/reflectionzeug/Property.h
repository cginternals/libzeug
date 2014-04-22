
#pragma once

#include <reflectionzeug/property_declaration.h>

#include <reflectionzeug/BoolProperty.h>
#include <reflectionzeug/ClassProperty.h>
#include <reflectionzeug/FilePathProperty.h>
#include <reflectionzeug/UnsignedIntegralProperty.h>
#include <reflectionzeug/SignedIntegralProperty.h>
#include <reflectionzeug/FloatingPointProperty.h>
#include <reflectionzeug/StringProperty.h>
#include <reflectionzeug/ArrayProperty.h>
#include <reflectionzeug/EnumProperty.h>

#include <reflectionzeug/Color.h>

#include <reflectionzeug/specialization_helpers.h>


namespace reflectionzeug
{

/** 
 * \defgroup property_specializations Property Specializations
 * \brief %All possible template specializations of Property
 *
 * Only this template class may be instantiated!
 * Supported Types:
 * - bool
 * - double
 * - float
 * - std::string
 * - FilePath
 * - any integral type
 * - any enum
 * - any class that implements (e.g. Color):
 *   \code{.cpp}
 *   static Class fromString(std::string string, bool * ok);
 *   std::string toString();
 *   \endcode
 * - any std::array of the above types
 *
 * The template specializations of supported types can have different super classes.
 * They have additional meta information, utility methods and common interfaces specific to each type. 
 * The specialization chosen for each type is determined via SFINAE (Substitution failure is not an error).
 * If you are going to extend the property class, keep in mind that all specializations 
 * have to somehow inherit from AbstractValueProperty. You will probably also have to extend your property visitor.
 *
 * \see \ref type_traits
 * \see AbstractPropertyVisitor
 * \see http://en.wikipedia.org/wiki/Substitution_failure_is_not_an_error
 */
/** \{ */

template <typename Type, typename>
class Property : public ClassProperty<Type>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name),
        ClassProperty<Type>(std::forward<Args>(args)...) {}
};

template <>
class Property<bool> : public BoolProperty
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name),
        BoolProperty(std::forward<Args>(args)...) {}
};

template <>
class Property<std::string> : public StringProperty
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name),
        StringProperty(std::forward<Args>(args)...) {}
};

template <>
class Property<FilePath> : public FilePathProperty
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name),
        FilePathProperty(std::forward<Args>(args)...) {}
};

template <typename Type>
class Property<Type, EnableIf<isUnsignedIntegral<Type>>> : public UnsignedIntegralProperty<Type>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name),
        UnsignedIntegralProperty<Type>(std::forward<Args>(args)...) {}
};

template <typename Type>
class Property<Type, EnableIf<isSignedIntegral<Type>>> : public SignedIntegralProperty<Type>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name),
        SignedIntegralProperty<Type>(std::forward<Args>(args)...) {}
};

template <typename Type>
class Property<Type, EnableIf<isFloatingPoint<Type>>> : public FloatingPointProperty<Type>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name), 
        FloatingPointProperty<Type>(std::forward<Args>(args)...) {}
};

template <typename Type>
class Property<Type, EnableIf<isArray<Type>>> : public ArrayProperty<typename Type::value_type, std::tuple_size<Type>::value>
{
public:
    Property(const std::string & name, const Type & array) :
        AbstractProperty(name),
        ArrayProperty<typename Type::value_type, std::tuple_size<Type>::value>(array) {}
    
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name),
        ArrayProperty<typename Type::value_type, std::tuple_size<Type>::value>(std::forward<Args>(args)...) {}
};

template <typename Type>
class Property<Type, EnableIf<std::is_enum<Type>>> : public EnumProperty<Type>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name),
        EnumProperty<Type>(std::forward<Args>(args)...) {}
};

/** \} */

} // namespace reflectionzeug
