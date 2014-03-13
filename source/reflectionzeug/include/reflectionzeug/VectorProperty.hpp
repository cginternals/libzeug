
#pragma once

#include <sstream>

#include <reflectionzeug/util.h>

namespace reflectionzeug
{

template <typename Type>
VectorProperty<Type>::VectorProperty(const std::string & name,
    const std::vector<Type> & value)
:   ValuePropertyInterface(name)
,   ValueProperty<std::vector<Type>>(name, value)
,   m_fixedSize((unsigned int)this->m_value->get().size())
,   m_columns(m_fixedSize)
,   m_rows(1)
{
    assert(m_fixedSize != 0);
}

template <typename Type>
VectorProperty<Type>::VectorProperty(const std::string & name,
    const std::function<std::vector<Type> ()> & getter,
    const std::function<void(const std::vector<Type> &)> & setter)
:   ValuePropertyInterface(name)
,   ValueProperty<std::vector<Type>>(name, getter, setter)
,   m_fixedSize((unsigned int)this->m_value->get().size())
,   m_columns(m_fixedSize)
,   m_rows(1)
{
    assert(m_fixedSize != 0);
}

template <typename Type>
template <class Object>
VectorProperty<Type>::VectorProperty(const std::string & name,
    Object & object, const std::vector<Type> & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const std::vector<Type> &))
:   ValuePropertyInterface(name)
,   ValueProperty<std::vector<Type>>(name, object, getter_pointer, setter_pointer)
,   m_fixedSize((unsigned int)this->m_value->get().size())
,   m_columns(m_fixedSize)
,   m_rows(1)
{
    assert(m_fixedSize != 0);
}

template <typename Type>
template <class Object>
VectorProperty<Type>::VectorProperty(const std::string & name,
    Object & object, std::vector<Type> (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const std::vector<Type> &))
:   ValuePropertyInterface(name)
,   ValueProperty<std::vector<Type>>(name, object, getter_pointer, setter_pointer)
,   m_fixedSize((unsigned int)this->m_value->get().size())
,   m_columns(m_fixedSize)
,   m_rows(1)
{
    assert(m_fixedSize != 0);
}

template <typename Type>
template <class Object>
VectorProperty<Type>::VectorProperty(const std::string & name,
    Object & object, std::vector<Type> (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(std::vector<Type>))
:   ValuePropertyInterface(name)
,   ValueProperty<std::vector<Type>>(name, object, getter_pointer, setter_pointer)
,   m_fixedSize((unsigned int)this->m_value->get().size())
,   m_columns(m_fixedSize)
,   m_rows(1)
{
    assert(m_fixedSize != 0);
}

template <typename Type>
std::vector<Type> VectorProperty<Type>::value() const
{
    assert(this->m_value->get().size() == m_fixedSize);
    return ValueProperty<std::vector<Type>>::value();
}

template <typename Type>
void VectorProperty<Type>::setValue(const std::vector<Type> & value)
{
    assert(value.size() == m_fixedSize);
    ValueProperty<std::vector<Type>>::setValue(value);
}

template <typename Type>
unsigned int VectorProperty<Type>::fixedSize() const
{
    return m_fixedSize;
}

template <typename Type>
unsigned int VectorProperty<Type>::columns() const
{
    return m_columns;
}

template <typename Type>
unsigned int VectorProperty<Type>::rows() const
{
    return m_rows;
}

template <typename Type>
void VectorProperty<Type>::setDimensions(unsigned int columns, unsigned int rows)
{
    assert(columns * rows == m_fixedSize);

    m_columns = columns;
    m_rows = rows;
}

template <typename Type>
std::string VectorProperty<Type>::toString() const
{
    std::vector<std::string> stringVector;

    for (const Type & element : this->value())
    {
        stringVector.push_back(elementToString(element));
    }

    return "(" + util::join(stringVector, ", ") + ")";
}

template <typename Type>
bool VectorProperty<Type>::fromString(const std::string & string)
{
    if (!matchesVectorRegex(string))
        return false;

    std::vector<std::string> values = util::extract(string, elementRegex());

    std::vector<Type> vector;
    for (std::string & value : values)
    {
        vector.push_back(elementFromString(value));
    }
    this->setValue(vector);

    return true;
}

template <typename Type>
bool VectorProperty<Type>::matchesVectorRegex(const std::string & string)
{
    std::stringstream vectorRegexStream;

    vectorRegexStream << "\\s*\\(";
    for (unsigned int i = 0; i < fixedSize() - 1; i++) {
        vectorRegexStream << "(" << elementRegex() << ")";
        vectorRegexStream << "\\s*,\\s*";
    }
    vectorRegexStream << elementRegex() << "\\)\\s*";

    return util::matchesRegex(string, vectorRegexStream.str());
}

} // namespace reflectionzeug
