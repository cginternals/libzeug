
#include <reflectionzeug/Variant.h>
#include <reflectionzeug/Typed.h>


namespace reflectionzeug
{


Variant::Variant()
: m_value(nullptr)
{
}

Variant::Variant(const Variant & variant)
: m_value(variant.m_value ? variant.m_value->createCopy() : nullptr)
{
}

Variant::Variant(char value)
: m_value(new Typed<char>(new AccessorValue<char>(value)))
{
}

Variant::Variant(unsigned char value)
: m_value(new Typed<unsigned char>(new AccessorValue<unsigned char>(value)))
{
}

Variant::Variant(short value)
: m_value(new Typed<short>(new AccessorValue<short>(value)))
{
}

Variant::Variant(unsigned short value)
: m_value(new Typed<unsigned short>(new AccessorValue<unsigned short>(value)))
{
}

Variant::Variant(int value)
: m_value(new Typed<int>(new AccessorValue<int>(value)))
{
}

Variant::Variant(unsigned int value)
: m_value(new Typed<int>(new AccessorValue<int>(value)))
{
}

Variant::Variant(long value)
: m_value(new Typed<long>(new AccessorValue<long>(value)))
{
}

Variant::Variant(unsigned long value)
: m_value(new Typed<unsigned long>(new AccessorValue<unsigned long>(value)))
{
}

Variant::Variant(long long value)
: m_value(new Typed<long long>(new AccessorValue<long long>(value)))
{
}

Variant::Variant(unsigned long long value)
: m_value(new Typed<unsigned long long>(new AccessorValue<unsigned long long>(value)))
{
}

Variant::Variant(float value)
: m_value(new Typed<float>(new AccessorValue<float>(value)))
{
}

Variant::Variant(double value)
: m_value(new Typed<double>(new AccessorValue<double>(value)))
{
}

Variant::Variant(const char * value)
: m_value(new Typed<std::string>(new AccessorValue<std::string>(std::string(value))))
{
}

Variant::Variant(const std::string & value)
: m_value(new Typed<std::string>(new AccessorValue<std::string>(value)))
{
}

/*
Variant::Variant(const std::vector<std::string> & value)
: m_value(new Typed< std::vector<std::string> >(new AccessorValue< std::vector<std::string> >(value)))
{
}
*/

bool Variant::isNull() const
{
    return !m_value;
}

const std::type_info & Variant::type() const
{
    if (m_value) {
        return m_value->type();
    } else {
        return typeid(void);
    }
}

Variant::~Variant()
{
    if (m_value)
    {
        delete m_value;
    }
}

Variant & Variant::operator=(const Variant & variant)
{
    if (m_value) {
        delete m_value;
    }

    m_value = variant.m_value ? variant.m_value->createCopy() : nullptr;

    return *this;
}


} // namespace reflectionzeug
