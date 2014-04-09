
#pragma once

#include <cassert>

#include <reflectionzeug/PropertyVisitor.h>
#include <reflectionzeug/util.h>

namespace reflectionzeug
{

template <typename Type>
template <typename... Arguments>
ArrayProperty<Type>::ArrayProperty(Arguments&&... args)
:   ValueProperty<Type>(std::forward<Arguments>(args)...)
,   m_columns(size())
,   m_rows(1)
{
}

template <typename Type>
ArrayProperty<Type>::~ArrayProperty()
{
}
    
template <typename Type>
void ArrayProperty<Type>::accept(AbstractPropertyVisitor * visitor, bool warn)
{
    auto * typedVisitor = dynamic_cast<PropertyVisitor<Type> *>(visitor);
    
    if (typedVisitor == nullptr)
    {
        ArrayPropertyInterface<contained_type>::accept(visitor, warn);
        return;
    }
    
    typedVisitor->visit(reinterpret_cast<Property<Type> *>(this));
}

template <typename Type>
unsigned int ArrayProperty<Type>::size() const
{
    static unsigned int size = Type().size();
    return size;
}

template <typename Type>
unsigned int ArrayProperty<Type>::columns() const
{
    return m_columns;
}

template <typename Type>
unsigned int ArrayProperty<Type>::rows() const
{
    return m_rows;
}

template <typename Type>
void ArrayProperty<Type>::setDimensions(unsigned int columns, unsigned int rows)
{
    assert(columns * rows == size());

    m_columns = columns;
    m_rows = rows;
}

template <typename Type>
std::string ArrayProperty<Type>::toString() const
{
    std::vector<std::string> stringVector;

    for (const contained_type & element : this->value())
    {
        stringVector.push_back(elementToString(element));
    }

    return "(" + util::join(stringVector, ", ") + ")";
}

template <typename Type>
bool ArrayProperty<Type>::fromString(const std::string & string)
{
    if (!matchesArrayRegex(string))
        return false;

    std::vector<std::string> values = util::extract(string, elementRegex());

    Type array;
    for (unsigned int i = 0; i < values.size(); ++i)
    {
        array[i] = (elementFromString(values[i]));
    }
    this->setValue(array);

    return true;
}

template <typename Type>
std::vector<typename Type::value_type> ArrayProperty<Type>::toVector() const
{
    Type array = this->value();
    return std::vector<contained_type>(array.begin(), array.end());
}

template <typename Type>
bool ArrayProperty<Type>::fromVector(const std::vector<contained_type> & vector)
{
    if (vector.size() < size())
        return false;

    Type array;
    for (unsigned int i = 0; i < size(); ++i)
        array[i] = vector[i];

    this->setValue(array);

    return true;
}

template <typename Type>
bool ArrayProperty<Type>::matchesArrayRegex(const std::string & string)
{
    std::stringstream vectorRegexStream;

    vectorRegexStream << "\\s*\\(";
    for (unsigned int i = 0; i < size() - 1; i++) {
        vectorRegexStream << "(" << elementRegex() << ")";
        vectorRegexStream << "\\s*,\\s*";
    }
    vectorRegexStream << elementRegex() << "\\)\\s*";

    return util::matchesRegex(string, vectorRegexStream.str());
}

} // namespace reflectionzeug
