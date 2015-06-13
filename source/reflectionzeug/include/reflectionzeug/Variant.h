
#pragma once


#include <string>
#include <vector>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


class AbstractValue;


/**
*  @brief
*    Variant typed value
*/
class REFLECTIONZEUG_API Variant
{
public:
    template <typename ValueType>
    static Variant fromValue(const ValueType & value);


public:
    /**
    *  @brief
    *    Constructor for an empty value
    */
    Variant();

    /**
    *  @brief
    *    Copy constructor
    *
    *  @param[in] variant
    *    Variant whose value will be copied
    */
    Variant(const Variant & variant);

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
    Variant(float value);
    Variant(double value);
    Variant(const char * value);
    Variant(const std::string & value);
    Variant(const std::vector<std::string> & value);

    Variant & operator=(const Variant & variant);

    bool isNull() const;

    const std::type_info & type() const;

    /** Returns true if the Variant has the template type ValueType.
     */
    template <typename ValueType>
    bool hasType() const;

    /** Returns the stored value converted to the template type ValueType. 
     * Call canConvert() to find out whether a type can be converted. 
     * If the value cannot be converted, a default-constructed value will be returned.
     */
    template <typename ValueType>
    ValueType value(const ValueType & defaultValue = ValueType()) const;

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Variant();


protected:
    AbstractValue * m_value;    /**< Typed value */
};


} // namespace reflectionzeug


#include <reflectionzeug/Variant.hpp>
