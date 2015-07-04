#pragma once

#include <reflectionzeug/Object.h>


template<typename Type>
class MyObject : public reflectionzeug::Object
{
public:
    const Type & constgetterconst() const
    {
        return m_var;
    }

    Type getterconst() const
    {
        return m_var;
    }

    void setterconst(const Type & var)
    {
        m_var = var;
    }

    void setter(Type var)
    {
        m_var = var;
    }

protected:
    Type m_var;
};