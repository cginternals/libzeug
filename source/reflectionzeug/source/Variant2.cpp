
#include <reflectionzeug/Variant2.h>


namespace reflectionzeug
{

Variant2::Variant2()
:   m_content(nullptr)
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
