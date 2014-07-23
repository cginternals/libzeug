
#include <reflectionzeug/Variant2.h>


namespace reflectionzeug
{

Variant2::Variant2()
:   m_content(nullptr)
{
}

Variant2::Variant2(const std::string & value)
:   m_content(new VariantHolder<std::string>(value))
{
}

Variant2::Variant2(float value)
:   m_content(new VariantHolder<float>(value))
{
}
Variant2::Variant2(double value)
:   m_content(new VariantHolder<double>(value))
{
}

Variant2::Variant2(char value)
:   m_content(new VariantHolder<char>(value))
{
}

Variant2::Variant2(unsigned char value)
:   m_content(new VariantHolder<unsigned char>(value))
{
}

Variant2::Variant2(short value)
:   m_content(new VariantHolder<short>(value))
{
}

Variant2::Variant2(unsigned short value)
:   m_content(new VariantHolder<unsigned short>(value))
{
}

Variant2::Variant2(int value)
:   m_content(new VariantHolder<int>(value))
{
}

Variant2::Variant2(unsigned int value)
:   m_content(new VariantHolder<unsigned int>(value))
{
}

Variant2::Variant2(long value)
:   m_content(new VariantHolder<long>(value))
{
}

Variant2::Variant2(unsigned long value)
:   m_content(new VariantHolder<unsigned long>(value))
{
}

Variant2::Variant2(long long value)
:   m_content(new VariantHolder<long long>(value))
{
}

Variant2::Variant2(unsigned long long value)
:   m_content(new VariantHolder<unsigned long long>(value))
{
}

Variant2::Variant2(const Variant2 & variant)
:   m_content(variant.m_content->clone())
{
}

Variant2::~Variant2()
{
    delete m_content;
}

bool Variant2::isNull() const
{
    return !m_content;
}

} // namespace reflectionzeug
