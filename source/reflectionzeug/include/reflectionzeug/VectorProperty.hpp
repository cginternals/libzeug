
#pragma once

#include <reflectionzeug/Utility.h>

namespace reflectionzeug
{
    
template <typename Vector>
VectorProperty<Vector>::VectorProperty(const std::string & name,
    const Vector & value)
:   ValuePropertyTemplate<Vector>(name, value)
,   m_fixedSize((unsigned int)this->m_value->get().size())
,   m_columns(m_fixedSize)
,   m_rows(1)
{
    assert(m_fixedSize != 0);
}

template <typename Vector>
VectorProperty<Vector>::VectorProperty(const std::string & name,
    const std::function<Vector ()> & getter,
    const std::function<void(const Vector &)> & setter)
:   ValuePropertyTemplate<Vector>(name, getter, setter)
,   m_fixedSize((unsigned int)this->m_value->get().size())
,   m_columns(m_fixedSize)
,   m_rows(1)
{
    assert(m_fixedSize != 0);
}

template <typename Vector>
template <class Object>
VectorProperty<Vector>::VectorProperty(const std::string & name,
    Object & object, const Vector & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Vector &))
:   ValuePropertyTemplate<Vector>(name, object, getter_pointer, setter_pointer)
,   m_fixedSize((unsigned int)this->m_value->get().size())
,   m_columns(m_fixedSize)
,   m_rows(1)
{
    assert(m_fixedSize != 0);
}

template <typename Vector>
template <class Object>
VectorProperty<Vector>::VectorProperty(const std::string & name,
    Object & object, Vector (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Vector &))
:   ValuePropertyTemplate<Vector>(name, object, getter_pointer, setter_pointer)
,   m_fixedSize((unsigned int)this->m_value->get().size())
,   m_columns(m_fixedSize)
,   m_rows(1)
{
    assert(m_fixedSize != 0);
}

template <typename Vector>
template <class Object>
VectorProperty<Vector>::VectorProperty(const std::string & name,
    Object & object, Vector (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Vector))
:   ValuePropertyTemplate<Vector>(name, object, getter_pointer, setter_pointer)
,   m_fixedSize((unsigned int)this->m_value->get().size())
,   m_columns(m_fixedSize)
,   m_rows(1)
{
    assert(m_fixedSize != 0);
}

template <typename Vector>
VectorProperty<Vector>::~VectorProperty()
{
}

template <typename Vector>
Vector VectorProperty<Vector>::value() const
{
    assert(this->m_value->get().size() == m_fixedSize);
    return ValuePropertyTemplate<Vector>::value();
}

template <typename Vector>
void VectorProperty<Vector>::setValue(const Vector & value)
{
    assert(value.size() == m_fixedSize);
    ValuePropertyTemplate<Vector>::setValue(value);
}
    
template <typename Vector>
unsigned int VectorProperty<Vector>::fixedSize() const
{
    return m_fixedSize;
}

template <typename Vector>
unsigned int VectorProperty<Vector>::columns() const
{
    return m_columns;
}

template <typename Vector>
unsigned int VectorProperty<Vector>::rows() const
{
    return m_rows;
}

template <typename Vector>
void VectorProperty<Vector>::setDimensions(unsigned int columns, unsigned int rows)
{    
    assert(columns * rows == m_fixedSize);
    
    m_columns = columns;
    m_rows = rows;
}

template <typename Vector>
std::string VectorProperty<Vector>::valueAsString() const
{
    return "(" + join(this->value(), ", ") + ")";
}
    
} // namespace reflectionzeug
