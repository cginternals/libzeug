
#pragma once

#include <reflectionzeug/Variant2.h>
#include <reflectionzeug/specialization_helpers.h>


namespace reflectionzeug
{

template <typename ValueType, typename = void>
struct VariantConverterInit
{
    void operator()()
    {
    }
};

template <typename ValueType>
struct VariantConverterInit<ValueType, EnableIf<std::is_integral<ValueType>>>
{
    void operator()()
    {
        Variant2::registerConverter<ValueType, bool>();
        Variant2::registerConverter<ValueType, char>();
        Variant2::registerConverter<ValueType, unsigned char>();
        Variant2::registerConverter<ValueType, short>();
        Variant2::registerConverter<ValueType, unsigned short>();
        Variant2::registerConverter<ValueType, int>();
        Variant2::registerConverter<ValueType, unsigned int>();
        Variant2::registerConverter<ValueType, long>();
        Variant2::registerConverter<ValueType, unsigned long>();
        Variant2::registerConverter<ValueType, long long>();
        Variant2::registerConverter<ValueType, unsigned long long>();
    }
};

template <typename ValueType>
struct VariantConverterInit<ValueType, EnableIf<std::is_floating_point<ValueType>>>
{
    void operator()()
    {
        Variant2::registerConverter<ValueType, float>();
        Variant2::registerConverter<ValueType, double>();
        Variant2::registerConverter<ValueType, long double>();
    }
};

} // namespace reflectionzeug
