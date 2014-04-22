
#include <iostream>

#include "SomeObject.h"

SomeObject::SomeObject()
:   m_count(0)
,   m_normalMode(NormalMode::Vertex)
,   m_normal({ 1.f, 2.f, 3.f })
{    
}

int SomeObject::count() const
{
    return m_count;
}

void SomeObject::setCount(const int & count)
{
    m_count = count;
}

void SomeObject::valueChanged(const int & value)
{
    std::cout << "Property value changed to \"" << value << "\"" << std::endl;
}

NormalMode SomeObject::normalMode() const
{
    return m_normalMode;
}

void SomeObject::setNormalMode(NormalMode mode)
{
    m_normalMode = mode;
}

float SomeObject::normal(size_t i) const
{
    return m_normal.at(i);
}

void SomeObject::setNormal(size_t i, float element)
{
    m_normal.at(i) = element;
}
