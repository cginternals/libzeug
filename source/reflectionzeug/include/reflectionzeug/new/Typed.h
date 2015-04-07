
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
//#include <reflectionzeug/new/TypedArray.h>


namespace reflectionzeug
{


/**
*  @brief
*    Helper selecting the used base class based on the specific type
*/
template <typename T, typename = void>
struct TypeSelector
{
    using Type = TypedClass<T>;
};

template <>
struct TypeSelector<bool>
{
    using Type = TypedBool;
};

template <>
struct TypeSelector<Color>
{
    using Type = TypedColor;
};

template <>
struct TypeSelector<std::string>
{
    using Type = TypedString;
};

template <>
struct TypeSelector<FilePath>
{
    using Type = TypedFilePath;
};

template <typename T>
struct TypeSelector<T, EnableIf<isSignedIntegral<T>>>
{
    using Type = TypedSignedIntegral<T>;
};

template <typename T>
struct TypeSelector<T, EnableIf<isUnsignedIntegral<T>>>
{
    using Type = TypedUnsignedIntegral<T>;
};

template <typename T>
struct TypeSelector<T, EnableIf<isFloatingPoint<T>>>
{
    using Type = TypedFloatingPoint<T>;
};

/*
template <typename T>
struct TypeSelector<T, EnableIf<isArray<T>>>
{
    using Type = TypedArray<typename T::value_type, std::tuple_size<T>::value>;
};

template <typename T>
struct PropertyClass<T, EnableIf<std::is_enum<T>>>
{
    using Type = EnumProperty<T>;
};
*/


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
};


} // namespace reflectionzeug


#include <reflectionzeug/new/Typed.hpp>
