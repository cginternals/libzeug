
#pragma once

#include <cassert>

#include <reflectionzeug/VariantHolder.h>
#include <reflectionzeug/VariantConverterRegistry.h>


namespace reflectionzeug
{

template <typename ValueType>
Variant2 Variant2::fromValue(const ValueType & value)
{
    Variant2 variant;
    variant.m_content = new VariantHolder<ValueType>(value);
    return variant;
}

template <typename FromType, typename ToType>
bool Variant2::registerConverter()
{
    auto & registry = VariantConverterRegistry<FromType>::instance();

    if (registry.canConvert(typeid(ToType)))
        return false;

    auto converter = [] (const FromType & input, void * output)
        {
            *static_cast<ToType *>(output) = static_cast<const ToType &>(input);
            return true;
        };

    return registry.registerConverter(typeid(ToType), converter);
}

template <typename FromType, typename ToType>
bool Variant2::registerConverter(ToType (FromType::*methodPtr)() const)
{
    auto & registry = VariantConverterRegistry<FromType>::instance();

    if (registry.canConvert(typeid(ToType)))
        return false;

    auto converter = [methodPtr] (const FromType & input, void * output)
        {
            *static_cast<ToType *>(output) = (input.*methodPtr)();
            return true;
        };

    return registry.registerConverter(typeid(ToType), converter);
}

template <typename FromType, typename ToType>
bool Variant2::registerConverter(ToType (FromType::*methodPtr)(bool * ok) const)
{
    auto & registry = VariantConverterRegistry<FromType>::instance();

    if (registry.canConvert(typeid(ToType)))
        return false;

    auto converter = [methodPtr] (const FromType & input, void * output)
        {
            bool ok;
            *static_cast<ToType *>(output) = (input.*methodPtr)(&ok);
            return ok;
        };

    return registry.registerConverter(typeid(ToType), converter);
}

template<typename FromType, typename ToType, typename FunctorType>
bool Variant2::registerConverter(FunctorType functor)
{
    auto & registry = VariantConverterRegistry<FromType>::instance();

    auto converter = [functor] (const FromType & input, void * output)
        {
            *static_cast<ToType *>(output) = functor(input);
            return true;
        };

    return registry.registerConverter(typeid(ToType), converter);
}

template <typename ValueType>
bool Variant2::hasType() const
{
    if (!m_content)
        return false;

    return typeid(ValueType) == m_content->type();
}

template <typename ValueType>
bool Variant2::canConvert() const
{
    if (!m_content)
        return false;

    if (typeid(ValueType) == m_content->type())
        return true;

    return m_content->canConvert(typeid(ValueType));
}

template <typename ValueType>
ValueType Variant2::value() const
{
    if (!m_content)
        return ValueType();

    if (typeid(ValueType) == m_content->type())
        return static_cast<VariantHolder<ValueType> *>(m_content)->value();

    ValueType value;
    bool ok = m_content->convert(typeid(ValueType), &value);

    if (!ok)
        return ValueType();

    return value;
}

} // namespace reflectionzeug
