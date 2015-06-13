
#pragma once


#include <reflectionzeug/type/specialization_helpers.h>
#include <reflectionzeug/type/TypedSignedIntegral.h>
#include <reflectionzeug/type/TypedUnsignedIntegral.h>
#include <reflectionzeug/type/TypedFloatingPoint.h>
#include <reflectionzeug/type/TypedBool.h>
#include <reflectionzeug/type/TypedString.h>
#include <reflectionzeug/type/TypedColor.h>
#include <reflectionzeug/type/TypedFilePath.h>
#include <reflectionzeug/type/TypedClass.h>
#include <reflectionzeug/type/TypedArray.h>
#include <reflectionzeug/type/TypedEnum.h>
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

template <typename T>
struct TypeSelector<T, EnableIf<isArray<T>>>
{
    using Type = TypedArray<typename T::value_type, std::tuple_size<T>::value>;
};

template <typename T>
struct TypeSelector<T, EnableIf<std::is_enum<T>>>
{
    using Type = TypedEnum<T>;
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

    virtual AbstractValue * createCopy() const override;
};


} // namespace reflectionzeug


#include <reflectionzeug/type/Typed.hpp>
