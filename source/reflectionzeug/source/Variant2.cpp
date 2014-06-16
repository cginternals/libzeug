
#include <reflectionzeug/Variant2.h>

#include <cassert>

#include <reflectionzeug/TypeId.h>


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

const std::type_info & Variant2::type() const
{
    return m_content->type();
}

bool Variant2::isNull() const
{
    return !m_content;
}

} // namespace reflectionzeug
