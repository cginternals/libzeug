
#pragma once


#include <reflectionzeug/type/specialization_helpers.h>
#include <reflectionzeug/type/PropertySignedIntegral.h>
#include <reflectionzeug/type/PropertyUnsignedIntegral.h>
#include <reflectionzeug/type/PropertyFloatingPoint.h>
#include <reflectionzeug/type/PropertyBool.h>
#include <reflectionzeug/type/PropertyString.h>
#include <reflectionzeug/type/PropertyColor.h>
#include <reflectionzeug/type/PropertyFilePath.h>
#include <reflectionzeug/type/PropertyClass.h>
#include <reflectionzeug/type/PropertyArray.h>
#include <reflectionzeug/type/PropertyEnum.h>
#include <reflectionzeug/type/AbstractVisitor.h>


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
*    Typed value
*/
template <typename T>
class Typed : public TypeSelector<T>::Type
{
public:
    template <typename... Args>
    Typed(Args&&... args);

    virtual ~Typed();

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/type/Typed.hpp>
