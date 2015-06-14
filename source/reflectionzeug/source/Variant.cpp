
#include <reflectionzeug/Variant.h>
#include <reflectionzeug/type/Typed.h>


namespace reflectionzeug
{


Variant Variant::array()
{
    Variant variant;
    variant.m_value = new Typed<VariantArray>(new AccessorValue<VariantArray>(VariantArray()));
    return variant;
}

Variant Variant::map()
{
    Variant variant;
    variant.m_value = new Typed<VariantMap>(new AccessorValue<VariantMap>(VariantMap()));
    return variant;
}

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

Variant::Variant(const std::vector<std::string> & value)
: m_value(new Typed< std::vector<std::string> >(new AccessorValue< std::vector<std::string> >(value)))
{
}

Variant::~Variant()
{
    if (m_value)
    {
        delete m_value;
    }
}

bool Variant::isNull() const
{
    return !m_value;
}

bool Variant::isArray() const
{
    return hasType<VariantArray>();
}

bool Variant::isMap() const
{
    return hasType<VariantMap>();
}

const std::type_info & Variant::type() const
{
    if (m_value) {
        return m_value->type();
    } else {
        return typeid(void);
    }
}

VariantArray * Variant::toArray()
{
    return ptr<VariantArray>();
}

const VariantArray * Variant::toArray() const
{
    return ptr<VariantArray>();
}

VariantMap * Variant::toMap()
{
    return ptr<VariantMap>();
}

const VariantMap * Variant::toMap() const
{
    return ptr<VariantMap>();
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
