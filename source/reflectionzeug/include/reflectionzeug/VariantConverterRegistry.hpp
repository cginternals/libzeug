
#pragma once

#include <reflectionzeug/VariantConverterInit.h>


namespace reflectionzeug
{

template <typename ValueType>
VariantConverterRegistry<ValueType> & VariantConverterRegistry<ValueType>::instance()
{
    static VariantConverterRegistry registry;
    registry.init();
    return registry;
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
bool VariantConverterRegistry<ValueType>::registerConverter(const std::type_info & typeInfo, const Converter & converter)
{
    if (canConvert(typeInfo))
        return false;

    m_converters.insert({ typeInfo, converter });
    return true;
}

template <typename ValueType>
VariantConverterRegistry<ValueType>::VariantConverterRegistry()
:   m_initialized(false)
{
}

template <typename ValueType>
VariantConverterRegistry<ValueType>::~VariantConverterRegistry()
{
}

template <typename ValueType>
void VariantConverterRegistry<ValueType>::init()
{    
    if (m_initialized)
        return;
        
    m_initialized = true;
    VariantConverterInit<ValueType>()();  
}

} // namespace reflectionzeug
