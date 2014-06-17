
#pragma once

#include <map>
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

    template <typename FromType, typename ToType>
    static bool registerConverter();

    template <typename FromType, typename ToType>
    static bool registerConverter(ToType (FromType::*methodPtr)() const);
    
    template <typename FromType, typename ToType>
    static bool registerConverter(ToType (FromType::*methodPtr)(bool * ok) const);

    template <typename FromType, typename ToType, typename FunctorType>
    static bool registerConverter(FunctorType functor);

public:
    Variant2();

    template <typename ValueType>
    Variant2(const ValueType & value);

    Variant2(const Variant2 & variant);

    ~Variant2();

    template <typename ValueType>
    bool hasType() const;

    bool isNull() const;

    template <typename ValueType>
    bool canConvert() const;

    template <typename ValueType>
    ValueType value() const;

private:
    VariantContent * m_content;
};

using VariantArray = std::vector<Variant2>;
using VariantMap = std::map<std::string, Variant2>;

} // namespace reflectionzeug

#include "Variant2.hpp"
