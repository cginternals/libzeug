
#pragma once

#include <functional>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>


namespace reflectionzeug
{

template <typename ValueType>
class VariantConverterRegistry
{
public:
    static VariantConverterRegistry & instance();

public:
    using Converter = std::function<bool (const ValueType & input, void * output)>;

    template <typename ConversionType>
    using TypedConverter = std::function<bool (const ValueType & input, ConversionType * output)>;

    template <typename ConversionType>
    bool registerConverter(const TypedConverter<ConversionType> & converter);

    bool canConvert(const std::type_info & typeInfo) const;

    bool convert(const ValueType & input, const std::type_info & typeInfo, void * output) const;

private:
    VariantConverterRegistry();
    ~VariantConverterRegistry();

    VariantConverterRegistry(const VariantConverterRegistry &) = delete;
    void operator=(const VariantConverterRegistry &) = delete;

private:
    std::unordered_map<std::type_index, Converter> m_converters;

};

} // namespace reflectionzeug

#include "VariantConverterRegistry.hpp"
