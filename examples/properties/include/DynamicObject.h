
#pragma once

class DynamicObject
{
public:
    DynamicObject() : m_apple_count(3) {};

    const int & appleCount() const;
    void setAppleCount(const int & count);
    
    

private:
    int m_apple_count;
};