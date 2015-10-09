
#include <reflectionzeug/variant/Variant.h>

#include <reflectionzeug/property/AccessorValue.h>
#include <reflectionzeug/tools/SerializerJSON.h>


namespace reflectionzeug
{


Variant Variant::array()
{
    Variant variant;
    variant.m_accessor = new AccessorValue<VariantArray>(VariantArray());
    return variant;
}

Variant Variant::array(size_t count)
{
    Variant variant;
    variant.m_accessor = new AccessorValue<VariantArray>(VariantArray(count));
    return variant;
}

Variant Variant::map()
{
    Variant variant;
    variant.m_accessor = new AccessorValue<VariantMap>(VariantMap());
    return variant;
}

Variant::Variant()
: m_accessor(nullptr)
{
}

Variant::Variant(const Variant & variant)
: m_accessor(variant.m_accessor ? variant.m_accessor->clone() : nullptr)
{
}

Variant::Variant(bool value)
: m_accessor(new AccessorValue<bool>(value))
{
}

Variant::Variant(char value)
: m_accessor(new AccessorValue<char>(value))
{
}

Variant::Variant(unsigned char value)
: m_accessor(new AccessorValue<unsigned char>(value))
{
}

Variant::Variant(short value)
: m_accessor(new AccessorValue<short>(value))
{
}

Variant::Variant(unsigned short value)
: m_accessor(new AccessorValue<unsigned short>(value))
{
}

Variant::Variant(int value)
: m_accessor(new AccessorValue<int>(value))
{
}

Variant::Variant(unsigned int value)
: m_accessor(new AccessorValue<int>(value))
{
}

Variant::Variant(long value)
: m_accessor(new AccessorValue<long>(value))
{
}

Variant::Variant(unsigned long value)
: m_accessor(new AccessorValue<unsigned long>(value))
{
}

Variant::Variant(long long value)
: m_accessor(new AccessorValue<long long>(value))
{
}

Variant::Variant(unsigned long long value)
: m_accessor(new AccessorValue<unsigned long long>(value))
{
}

Variant::Variant(float value)
: m_accessor(new AccessorValue<float>(value))
{
}

Variant::Variant(double value)
: m_accessor(new AccessorValue<double>(value))
{
}

Variant::Variant(const char * value)
: m_accessor(new AccessorValue<std::string>(std::string(value)))
{
}

Variant::Variant(const std::string & value)
: m_accessor(new AccessorValue<std::string>(value))
{
}

Variant::Variant(const std::vector<std::string> & value)
: m_accessor(new AccessorValue< std::vector<std::string> >(value))
{
}

Variant::Variant(const VariantArray & array)
: m_accessor(new AccessorValue<VariantArray>(array))
{
}

Variant::Variant(const VariantMap & map)
: m_accessor(new AccessorValue<VariantMap>(map))
{
}

Variant::~Variant()
{
    if (m_accessor)
    {
        delete m_accessor;
    }
}

bool Variant::isNull() const
{
    return !m_accessor;
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
    if (m_accessor) {
        return m_accessor->type();
    } else {
        return typeid(void);
    }
}

VariantArray * Variant::asArray()
{
    return ptr<VariantArray>();
}

const VariantArray * Variant::asArray() const
{
    return ptr<VariantArray>();
}

VariantMap * Variant::asMap()
{
    return ptr<VariantMap>();
}

const VariantMap * Variant::asMap() const
{
    return ptr<VariantMap>();
}

Variant & Variant::operator=(const Variant & variant)
{
    if (m_accessor) {
        delete m_accessor;
    }

    m_accessor = variant.m_accessor ? variant.m_accessor->clone() : nullptr;

    return *this;
}

std::string Variant::toJSON() const
{
    SerializerJSON json;
    return json.toString(*this);
}


} // namespace reflectionzeug
