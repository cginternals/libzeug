
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

    template <typename ValueType>
    static Variant fromValue(const ValueType && value);

    /** Returns Variant that stores an empty VariantArray.
     */
    static Variant array();

    /** Returns Variant that stores an empty VariantMap. 
     */
    static Variant map();

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

    Variant(const char * value);
    Variant(const std::string & value);
    
    Variant(float value);
    Variant(double value);
    
    Variant(char value);
    Variant(unsigned char value);
    Variant(short value);
    Variant(unsigned short value);
    Variant(int value);
    Variant(unsigned int value);
    Variant(long value);
    Variant(unsigned long value);
    Variant(long long value);
    Variant(unsigned long long value);

    Variant(const VariantArray & array);
    Variant(VariantArray && array);

    Variant(const VariantMap & map);
    Variant(VariantMap && map);

    Variant(const Variant & variant);
    Variant(Variant && variant);
    
    Variant & operator=(const Variant & variant);
    Variant & operator=(Variant && variant);

    ~Variant();

    /** Returns true if the Variant has the template type ValueType.
     */
    template <typename ValueType>
    bool hasType() const;

    bool isNull() const;

    bool isArray() const;
    bool isMap() const;

    /** Returns true if the Variant has or
     * can be converted to the template type ValueType.
     * \see registerConverter()
     */
    template <typename ValueType>
    bool canConvert() const;

    /** Returns the stored value converted to the template type ValueType. 
     * Call canConvert() to find out whether a type can be converted. 
     * If the value cannot be converted, a default-constructed value will be returned.
     */
    template <typename ValueType>
    ValueType value(const ValueType & defaultValue = ValueType()) const;

    /** Returns a pointer to the stored value if it has the template type ValueType.
     * Otherwise returns nullptr.
     */
    template <typename ValueType>
    ValueType * ptr();

    /** Convenience method. Does the same as calling 
     * \code variant.ptr<VariantArray>() \endcode
     */
    VariantArray * toArray();

    /** Convenience method. Does the same as calling
     * \code variant.ptr<VariantMap>() \endcode
     */
    VariantMap * toMap();

private:
    VariantContent * m_content;
};

} // namespace reflectionzeug

#include <reflectionzeug/Variant.hpp>
