
#pragma once


#include <reflectionzeug/specialization_helpers.h>
#include <reflectionzeug/new/TypedSignedIntegral.h>
#include <reflectionzeug/new/TypedUnsignedIntegral.h>
#include <reflectionzeug/new/TypedFloatingPoint.h>
#include <reflectionzeug/new/TypedBool.h>
#include <reflectionzeug/new/TypedString.h>
#include <reflectionzeug/new/TypedColor.h>
#include <reflectionzeug/new/TypedFilePath.h>
#include <reflectionzeug/new/TypedClass.h>


namespace reflectionzeug
{


/**
*  @brief
*    Helper selecting the used base class based on the specific type
*/
template <typename T, typename Accessor, typename = void>
struct TypeSelector
{
    using Type = TypedClass<T, Accessor>;
};

template <typename Accessor>
struct TypeSelector<bool, Accessor>
{
    using Type = TypedBool<Accessor>;
};

template <typename Accessor>
struct TypeSelector<Color, Accessor>
{
    using Type = TypedColor<Accessor>;
};

template <typename Accessor>
struct TypeSelector<std::string, Accessor>
{
    using Type = TypedString<Accessor>;
};

template <typename Accessor>
struct TypeSelector<FilePath, Accessor>
{
    using Type = TypedFilePath<Accessor>;
};

template <typename T, typename Accessor>
struct TypeSelector<T, Accessor, EnableIf<isSignedIntegral<T>>>
{
    using Type = TypedSignedIntegral<T, Accessor>;
};

template <typename T, typename Accessor>
struct TypeSelector<T, Accessor, EnableIf<isUnsignedIntegral<T>>>
{
    using Type = TypedUnsignedIntegral<T, Accessor>;
};

template <typename T, typename Accessor>
struct TypeSelector<T, Accessor, EnableIf<isFloatingPoint<T>>>
{
    using Type = TypedFloatingPoint<T, Accessor>;
};

/*
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
*/


/**
*  @brief
*    Implementation of a typed value for a specific type
*/
template <typename T, typename Accessor>
class TypedImpl : public TypeSelector<T, Accessor>::Type
{
public:
    TypedImpl(const Accessor & accessor);
    virtual ~TypedImpl();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedImpl.hpp>
