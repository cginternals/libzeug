
#pragma once

namespace zeug {
    
template <typename Vector>
VectorProperty<Vector>::VectorProperty(const std::string & name,
    const Vector & value)
:   ValueProperty<Vector>(name, value)
,   m_fixedSize(this->m_value->get().size())
,   m_columns(m_fixedSize)
,   m_rows(1)
{
    assert(m_fixedSize != 0);
}

template <typename Vector>
VectorProperty<Vector>::VectorProperty(const std::string & name,
    const std::function<const Vector & ()> & getter,
    const std::function<void(const Vector &)> & setter)
:   ValueProperty<Vector>(name, getter, setter)
,   m_fixedSize(this->m_value->get().size())
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
:   ValueProperty<Vector>(name, object, getter_pointer, setter_pointer)
,   m_fixedSize(this->m_value->get().size())
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
:   ValueProperty<Vector>(name, object, getter_pointer, setter_pointer)
,   m_fixedSize(this->m_value->get().size())
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
const Vector & VectorProperty<Vector>::value() const
{
    assert(this->m_value->get().size() == m_fixedSize);
    return ValueProperty<Vector>::value();
}

template <typename Vector>
void VectorProperty<Vector>::setValue(const Vector & value)
{
    assert(value.size() == m_fixedSize);
    ValueProperty<Vector>::setValue(value);
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
    
template <typename Vector>
std::string VectorProperty<Vector>::join(const Vector & vector,
    const std::string & separator) const
{
    std::stringstream stream;
    for (int i = 0; i < vector.size() - 1; i++)
        stream << vector.at(i) << separator;
    stream << vector.back();
    return stream.str();
}
    
} // namespace
