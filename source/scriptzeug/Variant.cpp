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
    return m_value.m_int;
}

bool Variant::isFloat() const
{
    return (m_type == Float);
}

float Variant::floatValue() const
{
    return m_value.m_float;
}

bool Variant::isString() const
{
    return (m_type == String);
}

std::string Variant::stringValue() const
{
    return m_string;
}


} // namespace
