#pragma once

#include <reflectionzeug/property_declaration.h>

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

#include <reflectionzeug/Color.h>

#include <reflectionzeug/specialization_helpers.h>

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

template <typename Type, typename>
class Property : public ClassProperty<Type>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name),
        ClassProperty<Type>(std::forward<Args>(args)...) {}

    virtual void accept(AbstractPropertyVisitor * visitor)
    {
        auto * typedVisitor = visitor->asVisitor<Property<Type>>();

        if (typedVisitor == nullptr)
            return ClassProperty<Type>::accept(visitor);

        typedVisitor->visit(this);
    }
};

template <typename Type>
class Property<Type, EnableIf<isArray<Type>>> : public ArrayProperty<typename Type::value_type, std::tuple_size<Type>::value>
{
public:
    using SuperClass = ArrayProperty<typename Type::value_type, std::tuple_size<Type>::value>;
public:
    Property(const std::string & name, const Type & array) :
        AbstractProperty(name),
        ArrayProperty<typename Type::value_type, std::tuple_size<Type>::value>(array) {}
    
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        AbstractProperty(name),
        SuperClass(std::forward<Args>(args)...) {}

    virtual void accept(AbstractPropertyVisitor * visitor)
    {
        auto * typedVisitor = visitor->asVisitor<Property<Type>>();

        if (typedVisitor == nullptr)
            return SuperClass::accept(visitor);

        typedVisitor->visit(this);
    }
};

} // namespace reflectionzeug

#define P_PROPERTY_SPEC_SINGLE(PropertyType) \
    namespace reflectionzeug \
    { \
    template <> \
    class Property<typename PropertyType::Type> : public PropertyType \
    { \
    public: \
        using Type = typename PropertyType::Type; \
    \
    public: \
        template <typename... Args> \
        Property(const std::string & name, Args&&... args) : \
            AbstractProperty(name), \
            PropertyType(std::forward<Args>(args)...) {} \
    \
        virtual void accept(AbstractPropertyVisitor * visitor) \
        { \
            auto * typedVisitor = visitor->asVisitor<Property<Type>>(); \
    \
            if (typedVisitor == nullptr) \
                return PropertyType::accept(visitor); \
    \
            typedVisitor->visit(this); \
        } \
    }; \
    }
    
#define P_PROPERTY_SPEC_MULTIPLE(PropertyType) \
    namespace reflectionzeug \
    { \
    template <typename Type> \
    class Property<Type, EnableIf<typename PropertyType<Type>::Trait>> : public PropertyType<Type> \
    { \
    public: \
        template <typename... Args> \
        Property(const std::string & name, Args&&... args) : \
            AbstractProperty(name), \
            PropertyType<Type>(std::forward<Args>(args)...) {} \
    \
        virtual void accept(AbstractPropertyVisitor * visitor) \
        { \
            auto * typedVisitor = visitor->asVisitor<Property<Type>>(); \
    \
            if (typedVisitor == nullptr) \
                return PropertyType<Type>::accept(visitor); \
    \
            typedVisitor->visit(this); \
        } \
    }; \
    }
    
P_PROPERTY_SPEC_SINGLE(reflectionzeug::BoolProperty)
P_PROPERTY_SPEC_SINGLE(reflectionzeug::StringProperty)
P_PROPERTY_SPEC_SINGLE(reflectionzeug::ColorProperty)
P_PROPERTY_SPEC_SINGLE(reflectionzeug::FilePathProperty)

P_PROPERTY_SPEC_MULTIPLE(reflectionzeug::UnsignedIntegralProperty)
P_PROPERTY_SPEC_MULTIPLE(reflectionzeug::SignedIntegralProperty)
P_PROPERTY_SPEC_MULTIPLE(reflectionzeug::FloatingPointProperty)
P_PROPERTY_SPEC_MULTIPLE(reflectionzeug::EnumProperty)

/** \} */
