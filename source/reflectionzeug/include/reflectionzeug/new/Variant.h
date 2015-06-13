
#pragma once


#include <string>
#include <vector>

#include <reflectionzeug/reflectionzeug_api.h>


#include <reflectionzeug/new/Typed.h>


namespace reflectionzeug
{


class AbstractValue;


/**
*  @brief
*    Variant typed value
*/
class REFLECTIONZEUG_API Variant2
{
public:
    template <typename ValueType>
    static Variant2 fromValue(const ValueType & value)
    {
        Variant2 variant;
        variant.m_value = new Typed<ValueType>(new AccessorValue<ValueType>(value));
        return variant;
    }


public:
    /**
    *  @brief
    *    Constructor for an empty value
    */
    Variant2();

    /**
    *  @brief
    *    Copy constructor
    *
    *  @param[in] variant
    *    Variant whose value will be copied
    */
    Variant2(const Variant2 & variant);

    Variant2(char value);
    Variant2(unsigned char value);
    Variant2(short value);
    Variant2(unsigned short value);
    Variant2(int value);
    Variant2(unsigned int value);
    Variant2(long value);
    Variant2(unsigned long value);
    Variant2(long long value);
    Variant2(unsigned long long value);
    Variant2(float value);
    Variant2(double value);
    Variant2(const char * value);
    Variant2(const std::string & value);
    // [TODO]
//  Variant2(const std::vector<std::string> & value);

    Variant2 & operator=(const Variant2 & variant);

    bool isNull() const;

    const std::type_info & type() const;

    /** Returns true if the Variant has the template type ValueType.
     */
    template <typename ValueType>
    bool hasType() const
    {
        if (!m_value)
            return false;

        return typeid(ValueType) == m_value->type();
    }

    /** Returns the stored value converted to the template type ValueType. 
     * Call canConvert() to find out whether a type can be converted. 
     * If the value cannot be converted, a default-constructed value will be returned.
     */
    template <typename ValueType>
    ValueType value(const ValueType & defaultValue = ValueType()) const
    {
        if (m_value && typeid(ValueType) == m_value->type()) {
            return static_cast<Typed<ValueType> *>(m_value)->value();
        } else {
            return defaultValue;
        }
    }

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Variant2();


protected:
    AbstractValue * m_value;    /**< Typed value */
};


} // namespace reflectionzeug
