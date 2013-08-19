
#pragma once

namespace propertyzeug {
    class AbstractProperty;
}

class SomeObject
{
public:
    SomeObject() : m_count(0) {};

    const int & count() const;
    void setCount(const int & count);

    void propertyChanged(propertyzeug::AbstractProperty & property);
    
private:
    int m_count;
};