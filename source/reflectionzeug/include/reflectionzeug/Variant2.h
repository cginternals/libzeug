
#pragma once

#include <map>
#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{

class VariantContent;

class REFLECTIONZEUG_API Variant2 
{
public:
    template <typename ValueType>
    static Variant2 fromValue(const ValueType & value);

public:
    Variant2();

    template <typename ValueType>
    Variant2(const ValueType & value);

    Variant2(const Variant2 & variant);

    const std::type_info & type() const;

    template <typename ValueType>
    const ValueType & to() const;
    
    bool isNull() const;

    template <typename ValueType>
    bool canConvert() const;

    template <typename ValueType>
    bool convert(); 

private:
    std::unique_ptr<VariantContent> m_content;
};

using VariantArray = std::vector<Variant2>;
using VariantMap = std::map<std::string, Variant2>;

class REFLECTIONZEUG_API VariantContent
{
public:
    virtual ~VariantContent() = default;
    virtual VariantContent * clone() const = 0;

    virtual const std::type_info & type() const = 0;

    virtual bool canConvert(const std::type_info & typeInfo) const = 0;
    virtual bool convert(const std::type_info & typeInfo, void * result) const = 0;
};

} // namespace reflectionzeug

#include "Variant2.hpp"
