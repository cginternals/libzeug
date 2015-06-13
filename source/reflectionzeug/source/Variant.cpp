
#include <reflectionzeug/Variant.h>
#include <reflectionzeug/Typed.h>


namespace reflectionzeug
{


Variant2::Variant2()
: m_value(nullptr)
{
}

Variant2::Variant2(const Variant2 & variant)
: m_value(variant.m_value ? variant.m_value->createCopy() : nullptr)
{
}

Variant2::Variant2(char value)
: m_value(new Typed<char>(new AccessorValue<char>(value)))
{
}

Variant2::Variant2(unsigned char value)
: m_value(new Typed<unsigned char>(new AccessorValue<unsigned char>(value)))
{
}

Variant2::Variant2(short value)
: m_value(new Typed<short>(new AccessorValue<short>(value)))
{
}

Variant2::Variant2(unsigned short value)
: m_value(new Typed<unsigned short>(new AccessorValue<unsigned short>(value)))
{
}

Variant2::Variant2(int value)
: m_value(new Typed<int>(new AccessorValue<int>(value)))
{
}

Variant2::Variant2(unsigned int value)
: m_value(new Typed<int>(new AccessorValue<int>(value)))
{
}

Variant2::Variant2(long value)
: m_value(new Typed<long>(new AccessorValue<long>(value)))
{
}

Variant2::Variant2(unsigned long value)
: m_value(new Typed<unsigned long>(new AccessorValue<unsigned long>(value)))
{
}

Variant2::Variant2(long long value)
: m_value(new Typed<long long>(new AccessorValue<long long>(value)))
{
}

Variant2::Variant2(unsigned long long value)
: m_value(new Typed<unsigned long long>(new AccessorValue<unsigned long long>(value)))
{
}

Variant2::Variant2(float value)
: m_value(new Typed<float>(new AccessorValue<float>(value)))
{
}

Variant2::Variant2(double value)
: m_value(new Typed<double>(new AccessorValue<double>(value)))
{
}

Variant2::Variant2(const char * value)
: m_value(new Typed<std::string>(new AccessorValue<std::string>(std::string(value))))
{
}

Variant2::Variant2(const std::string & value)
: m_value(new Typed<std::string>(new AccessorValue<std::string>(value)))
{
}

/*
Variant2::Variant2(const std::vector<std::string> & value)
: m_value(new Typed< std::vector<std::string> >(new AccessorValue< std::vector<std::string> >(value)))
{
}
*/

bool Variant2::isNull() const
{
    return !m_value;
}

const std::type_info & Variant2::type() const
{
    if (m_value) {
        return m_value->type();
    } else {
        return typeid(void);
    }
}

Variant2::~Variant2()
{
    if (m_value)
    {
        delete m_value;
    }
}

Variant2 & Variant2::operator=(const Variant2 & variant)
{
    if (m_value) {
        delete m_value;
    }

    m_value = variant.m_value ? variant.m_value->createCopy() : nullptr;

    return *this;
}


} // namespace reflectionzeug
