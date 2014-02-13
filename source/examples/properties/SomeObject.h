
#pragma once

namespace propertyzeug 
{
    class AbstractProperty;
}

class SomeObject
{
public:
    SomeObject() : m_count(0) {};

    int count() const;
    void setCount(const int & count);

    void valueChanged(const int & value);
    
private:
    int m_count;
};