
#pragma once

#include <functional>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

#include <reflectionzeug/specialization_helpers.h>


namespace reflectionzeug
{

template <typename ValueType>
class VariantConverterRegistry
{
public:
    static VariantConverterRegistry & instance();
    
public:
    using Converter = std::function<bool (const ValueType & input, void * output)>;
    
    bool registerConverter(const std::type_info & typeInfo, const Converter & converter);

    bool canConvert(const std::type_info & typeInfo) const;

    bool convert(const ValueType & input, const std::type_info & typeInfo, void * output) const;

private:
    VariantConverterRegistry();
    ~VariantConverterRegistry();

    VariantConverterRegistry(const VariantConverterRegistry &) = delete;
    void operator=(const VariantConverterRegistry &) = delete;
    
    void init();

private:
    std::unordered_map<std::type_index, Converter> m_converters;
    bool m_initialized;
};

} // namespace reflectionzeug

#include "VariantConverterRegistry.hpp"
