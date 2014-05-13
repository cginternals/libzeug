
#pragma once

#include <array>


enum class NormalMode : char { Vertex, Custom, LookAt };

class SomeObject
{
public:
    SomeObject();

    int count() const;
    void setCount(const int & count);
    
    NormalMode normalMode() const;
    void setNormalMode(NormalMode mode);
    
    float normal(size_t i) const;
    void setNormal(size_t i, float elementl);

    void valueChanged(const int & value);
    
private:
    int m_count;
    NormalMode m_normalMode;
    std::array<float, 3> m_normal;
};