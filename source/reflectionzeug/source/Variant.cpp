
#include <reflectionzeug/Variant.h>


namespace reflectionzeug
{

Variant Variant::array()
{
    Variant variant;
    variant.m_content = new VariantHolder<VariantArray>({});
    return variant;
}

Variant Variant::map()
{
    Variant variant;
    variant.m_content = new VariantHolder<VariantMap>(VariantMap());
    return variant;
}

Variant::Variant()
:   m_content(nullptr)
{
}

Variant::Variant(const char * value)
:   m_content(new VariantHolder<std::string>(std::string(value)))
{
}

Variant::Variant(const std::string & value)
:   m_content(new VariantHolder<std::string>(value))
{
}

Variant::Variant(float value)
:   m_content(new VariantHolder<float>(value))
{
}
Variant::Variant(double value)
:   m_content(new VariantHolder<double>(value))
{
}

Variant::Variant(char value)
:   m_content(new VariantHolder<char>(value))
{
}

Variant::Variant(unsigned char value)
:   m_content(new VariantHolder<unsigned char>(value))
{
}

Variant::Variant(short value)
:   m_content(new VariantHolder<short>(value))
{
}

Variant::Variant(unsigned short value)
:   m_content(new VariantHolder<unsigned short>(value))
{
}

Variant::Variant(int value)
:   m_content(new VariantHolder<int>(value))
{
}

Variant::Variant(unsigned int value)
:   m_content(new VariantHolder<unsigned int>(value))
{
}

Variant::Variant(long value)
:   m_content(new VariantHolder<long>(value))
{
}

Variant::Variant(unsigned long value)
:   m_content(new VariantHolder<unsigned long>(value))
{
}

Variant::Variant(long long value)
:   m_content(new VariantHolder<long long>(value))
{
}

Variant::Variant(unsigned long long value)
:   m_content(new VariantHolder<unsigned long long>(value))
{
}

Variant::Variant(const VariantArray & array)
:   m_content(new VariantHolder<VariantArray>(array))
{
}

Variant::Variant(VariantArray && array)
:   m_content(new VariantHolder<VariantArray>(std::move(array)))
{
}

Variant::Variant(const VariantMap & map)
:   m_content(new VariantHolder<VariantMap>(map))
{
}

Variant::Variant(VariantMap && map)
:   m_content(new VariantHolder<VariantMap>(std::move(map)))
{
}

Variant::Variant(const Variant & variant)
:   m_content(!variant.m_content ? nullptr : variant.m_content->clone())
{
}

Variant::Variant(Variant && variant)
:   m_content(nullptr)
{
    std::swap(m_content, variant.m_content);
}

Variant & Variant::operator=(const Variant & variant)
{
    if (m_content)
        delete m_content;
        
    m_content = !variant.m_content ? nullptr : variant.m_content->clone();
    return *this;
}

Variant & Variant::operator=(Variant && variant)
{
    std::swap(m_content, variant.m_content);
    return *this;
}

Variant::~Variant()
{
    if (m_content)
        delete m_content;
}

bool Variant::isNull() const
{
    return !m_content;
}

bool Variant::isArray() const
{
    return hasType<VariantArray>();
}

bool Variant::isMap() const
{
    return hasType<VariantMap>();
}

VariantArray * Variant::toArray()
{
    return ptr<VariantArray>();
}

VariantMap * Variant::toMap()
{
    return ptr<VariantMap>();
}

} // namespace reflectionzeug
