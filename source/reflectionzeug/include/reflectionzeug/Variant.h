
#pragma once

#include <map>
#include <string>
#include <typeinfo>
#include <vector>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{

class Variant;
class VariantContent;

using VariantArray = std::vector<Variant>;
using VariantMap = std::map<std::string, Variant>;

class REFLECTIONZEUG_API Variant 
{
public:
    template <typename ValueType>
    static Variant fromValue(const ValueType & value);

    template <typename FromType, typename ToType>
    static bool registerConverter();

    template <typename FromType, typename ToType>
    static bool registerConverter(ToType (FromType::*methodPtr)() const);
    
    template <typename FromType, typename ToType>
    static bool registerConverter(ToType (FromType::*methodPtr)(bool * ok) const);

    template <typename FromType, typename ToType, typename FunctorType>
    static bool registerConverter(FunctorType functor);

public:
    Variant();

    explicit Variant(const std::string & value);
    
    explicit Variant(float value);
    explicit Variant(double value);
    
    explicit Variant(char value);
    explicit Variant(unsigned char value);
    explicit Variant(short value);
    explicit Variant(unsigned short value);
    explicit Variant(int value);
    explicit Variant(unsigned int value);
    explicit Variant(long value);
    explicit Variant(unsigned long value);
    explicit Variant(long long value);
    explicit Variant(unsigned long long value);
    
    explicit Variant(const VariantArray & array);
    explicit Variant(const VariantMap & map);

    Variant(const Variant & variant);
    
    Variant & operator=(const Variant & variant);

    ~Variant();

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

#include "Variant.hpp"
