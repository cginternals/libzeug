
#include <iostream>

#include "SomeObject.h"


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
