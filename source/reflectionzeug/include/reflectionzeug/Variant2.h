
#pragma once

#include <map>
#include <string>
#include <typeinfo>
#include <vector>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{

class Variant2;
class VariantContent;

using VariantArray = std::vector<Variant2>;
using VariantMap = std::map<std::string, Variant2>;

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

    explicit Variant2(const std::string & value);
    
    explicit Variant2(float value);
    explicit Variant2(double value);
    
    explicit Variant2(char value);
    explicit Variant2(unsigned char value);
    explicit Variant2(short value);
    explicit Variant2(unsigned short value);
    explicit Variant2(int value);
    explicit Variant2(unsigned int value);
    explicit Variant2(long value);
    explicit Variant2(unsigned long value);
    explicit Variant2(long long value);
    explicit Variant2(unsigned long long value);
    
    explicit Variant2(const VariantArray & array);
    explicit Variant2(const VariantMap & map);

    Variant2(const Variant2 & variant);
    
    Variant2 & operator=(const Variant2 & variant);

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

} // namespace reflectionzeug

#include "Variant2.hpp"
