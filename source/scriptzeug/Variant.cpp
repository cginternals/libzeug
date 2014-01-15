#include <scriptzeug/Variant.h>


namespace scriptzeug
{


Variant::Variant()
: m_type(Unknown)
{
}

Variant::Variant(const Variant & rh)
: m_type(rh.m_type)
, m_value(rh.m_value)
{
}

Variant::Variant(int value)
: m_type(Int)
{
    m_value.m_int = value;
}

Variant::Variant(float value)
: m_type(Float)
{
    m_value.m_float = value;
}

Variant::Variant(const std::string & value)
: m_type(String)
, m_string(value)
{
}

Variant::~Variant()
{
}

Variant & Variant::operator =(const Variant & rh)
{
    m_type   = rh.m_type;
    m_value  = rh.m_value;
    m_string = m_string;
    return *this;
}

Variant::Type Variant::type() const
{
    return m_type;
}

bool Variant::isInt() const
{
    return (m_type == Int);
}

int Variant::intValue() const
{
    switch (m_type) {
        case Int:    return m_value.m_int;
        case Float:  return (int)m_value.m_float;
        case String:
        default:     return 0;
    }
}

bool Variant::isFloat() const
{
    return (m_type == Float);
}

float Variant::floatValue() const
{
    switch (m_type) {
        case Int:    return (float)m_value.m_int;
        case Float:  return m_value.m_float;
        case String:
        default:     return 0.0f;
    }
}

bool Variant::isString() const
{
    return (m_type == String);
}

std::string Variant::stringValue() const
{
    switch (m_type) {
        case String: return m_string;
        case Int:
        case Float:
        default:     return "";
    }
}


} // namespace
