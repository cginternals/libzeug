
#pragma once


#include <reflectionzeug/property/specialization_helpers.h>
#include <reflectionzeug/property/PropertySignedIntegral.h>
#include <reflectionzeug/property/PropertyUnsignedIntegral.h>
#include <reflectionzeug/property/PropertyFloatingPoint.h>
#include <reflectionzeug/property/PropertyBool.h>
#include <reflectionzeug/property/PropertyString.h>
#include <reflectionzeug/property/PropertyColor.h>
#include <reflectionzeug/property/PropertyFilePath.h>
#include <reflectionzeug/property/PropertyClass.h>
#include <reflectionzeug/property/PropertyArray.h>
#include <reflectionzeug/property/PropertyEnum.h>
#include <reflectionzeug/property/AbstractVisitor.h>


namespace reflectionzeug
{


/**
*  @brief
*    Helper selecting the used base class based on the specific type
*/
template <typename T, typename = void>
struct TypeSelector
{
    using Type = PropertyClass<T>;
};

template <>
struct TypeSelector<bool>
{
    using Type = PropertyBool;
};

template <>
struct TypeSelector<Color>
{
    using Type = PropertyColor;
};

template <>
struct TypeSelector<std::string>
{
    using Type = PropertyString;
};

template <>
struct TypeSelector<FilePath>
{
    using Type = PropertyFilePath;
};

template <typename T>
struct TypeSelector<T, EnableIf<isSignedIntegral<T>>>
{
    using Type = PropertySignedIntegral<T>;
};

template <typename T>
struct TypeSelector<T, EnableIf<isUnsignedIntegral<T>>>
{
    using Type = PropertyUnsignedIntegral<T>;
};

template <typename T>
struct TypeSelector<T, EnableIf<isFloatingPoint<T>>>
{
    using Type = PropertyFloatingPoint<T>;
};

template <typename T>
struct TypeSelector<T, EnableIf<isArray<T>>>
{
    using Type = PropertyArray<typename T::value_type, std::tuple_size<T>::value>;
};

template <typename T>
struct TypeSelector<T, EnableIf<std::is_enum<T>>>
{
    using Type = PropertyEnum<T>;
};


/**
*  @brief
*    Property
*/
template <typename T>
class Property : public TypeSelector<T>::Type
{
public:
    template <typename... Args>
    Property(Args&&... args);

    virtual ~Property();

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/Property.hpp>
