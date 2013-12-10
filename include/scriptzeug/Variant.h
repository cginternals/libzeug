#pragma once


#include <string>
#include <scriptzeug/scriptzeug.h>


namespace scriptzeug
{


/** \brief Container for a variable-typed value
 */
class SCRIPTZEUG_API Variant
{
public:
    enum Type {
        Unknown = 0,
        Int,
        Float,
        String
    };

public:
    Variant();
    Variant(const Variant & rh);
    Variant(int value);
    Variant(float value);
    Variant(const std::string & value);
    ~Variant();

    Variant & operator =(const Variant & rh);

    bool isInt() const;
    int intValue() const;

    bool isFloat() const;
    float floatValue() const;

    bool isString() const;
    std::string stringValue() const;

    Type type() const;

protected:
    Type m_type;
    union {
        int   m_int;
        float m_float;
    } m_value;
    std::string m_string;
};


} // namespace scriptzeug
