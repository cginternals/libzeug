#pragma once

#include <reflectionzeug/property_declaration.h>

#include <reflectionzeug/AbstractValueProperty.h>
#include <reflectionzeug/BoolProperty.h>
#include <reflectionzeug/ClassProperty.h>
#include <reflectionzeug/ColorProperty.h>
#include <reflectionzeug/FilePathProperty.h>
#include <reflectionzeug/UnsignedIntegralProperty.h>
#include <reflectionzeug/SignedIntegralProperty.h>
#include <reflectionzeug/FloatingPointProperty.h>
#include <reflectionzeug/StringProperty.h>
#include <reflectionzeug/ArrayProperty.h>
#include <reflectionzeug/EnumProperty.h>

/**
 * \defgroup property_specializations Property Specializations
 * \brief All possible template specializations of Property
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

namespace reflectionzeug
{

template <typename T, typename = void>
struct PropertyClass
{
    using Type = ClassProperty<T>;
};

template <>
struct PropertyClass<BoolProperty::Type>
{
    using Type = BoolProperty;
};

template <>
struct PropertyClass<ColorProperty::Type>
{
	using Type = ColorProperty;
};

template <>
struct PropertyClass<StringProperty::Type>
{
    using Type = StringProperty;
};

template <>
struct PropertyClass<FilePathProperty::Type>
{
    using Type = FilePathProperty;
};

template <typename T>
struct PropertyClass<T, EnableIf<isArray<T>>>
{
    using Type = ArrayProperty<typename T::value_type, std::tuple_size<T>::value>;
};

template <typename T>
struct PropertyClass<T, EnableIf<std::is_enum<T>>>
{
	using Type = EnumProperty<T>;
};

template <typename T>
struct PropertyClass<T, EnableIf<isUnsignedIntegral<T>>>
{
    using Type = UnsignedIntegralProperty<T>;
};

template <typename T>
struct PropertyClass<T, EnableIf<isSignedIntegral<T>>>
{
    using Type = SignedIntegralProperty<T>;
};

template <typename T>
struct PropertyClass<T, EnableIf<isFloatingPoint<T>>>
{
    using Type = FloatingPointProperty<T>;
};

template <typename Type>
class Property : public PropertyClass<Type>::Type
{
    static_assert(std::is_base_of<AbstractValueProperty, typename PropertyClass<Type>::Type>::value,
                  "Super class must inherit from AbstractValueProperty");

    static_assert(isPlain<Type>::value,
                  "Type must not have any specifiers and must not be a reference.");

public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args)
    :   AbstractProperty(name)
    {
        this->setAccessors(std::forward<Args>(args)...);
    }

    virtual void accept(AbstractPropertyVisitor * visitor)
    {
        auto * typedVisitor = visitor->asVisitor<Property<Type>>();

        if (typedVisitor == nullptr)
            return PropertyClass<Type>::Type::accept(visitor);

        typedVisitor->visit(this);
    }
};

} // namespace reflectionzeug

/** \} */
