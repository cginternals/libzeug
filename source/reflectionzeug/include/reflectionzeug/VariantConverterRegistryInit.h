
#pragma once

#include <reflectionzeug/specialization_helpers.h>
#include <reflectionzeug/VariantConverterRegistry.h>
#include <reflectionzeug/VariantConverters.h>


namespace reflectionzeug
{

template <typename ValueType, typename = void>
struct VariantConverterRegistryInit
{
    void operator()(VariantConverterRegistry<ValueType> & registry)
    {
    }
};

template <typename ValueType>
struct VariantConverterRegistryInit<ValueType, EnableIf<std::is_integral<ValueType>>>
{
    void operator()(VariantConverterRegistry<ValueType> & registry)
    {
        registry.template registerConverter<bool>(implicitConverter<ValueType, bool>);
        registry.template registerConverter<char>(implicitConverter<ValueType, char>);
        registry.template registerConverter<unsigned char>(implicitConverter<ValueType, unsigned char>);
        registry.template registerConverter<short>(implicitConverter<ValueType, short>);
        registry.template registerConverter<unsigned short>(implicitConverter<ValueType, unsigned short>);
        registry.template registerConverter<int>(implicitConverter<ValueType, int>);
        registry.template registerConverter<unsigned int>(implicitConverter<ValueType, unsigned int>);
        registry.template registerConverter<long>(implicitConverter<ValueType, long>);
        registry.template registerConverter<unsigned long>(implicitConverter<ValueType, unsigned long>);
        registry.template registerConverter<long long>(implicitConverter<ValueType, long long>);
        registry.template registerConverter<unsigned long long>(implicitConverter<ValueType, unsigned long long>);
    }
};

} // namespace reflectionzeug
