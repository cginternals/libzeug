
#include "DynamicObject.h"

const int & DynamicObject::appleCount() const
{
    return m_apple_count;
}

void DynamicObject::setAppleCount(const int & count)
{
    m_apple_count = count;
}