
#pragma once

#include <reflectionzeug/VariantConverterRegistryInit.h>


namespace reflectionzeug
{

template <typename ValueType>
VariantConverterRegistry<ValueType> & VariantConverterRegistry<ValueType>::instance()
{
    static VariantConverterRegistry registry;
    return registry;
}

template <typename ValueType>
template <typename ConversionType>
bool VariantConverterRegistry<ValueType>::registerConverter(const TypedConverter<ConversionType> & converter)
{
    if (m_converters.count(typeid(ConversionType)))
        return false;

    Converter typelessConverter = [converter] (const ValueType & input, void * output)
        {
            return converter(input, static_cast<ConversionType *>(output));
        };

    m_converters.insert({ typeid(ConversionType), typelessConverter });

    return true;
}

template <typename ValueType>
bool VariantConverterRegistry<ValueType>::canConvert(const std::type_info & typeInfo) const
{
    return m_converters.count(typeInfo);
}

template <typename ValueType>
bool VariantConverterRegistry<ValueType>::convert(
    const ValueType & input, 
    const std::type_info & typeInfo, 
    void * output) const
{
    if (!m_converters.count(typeInfo))
        return false;

    return m_converters.at(typeInfo)(input, output);
}

template <typename ValueType>
VariantConverterRegistry<ValueType>::VariantConverterRegistry()
{
    VariantConverterRegistryInit<ValueType>()(*this);
}

template <typename ValueType>
VariantConverterRegistry<ValueType>::~VariantConverterRegistry()
{
}

} // namespace reflectionzeug
