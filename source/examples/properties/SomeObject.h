
#pragma once

#include "PropertyExtension.h"


class SomeObject
{
public:
    SomeObject() : m_count(0), m_normalMode(NormalMode::Vertex) {};

    int count() const;
    void setCount(const int & count);
    
    NormalMode normalMode() const;
    void setNormalMode(NormalMode mode);

    void valueChanged(const int & value);
    
private:
    int m_count;
    NormalMode m_normalMode;
};