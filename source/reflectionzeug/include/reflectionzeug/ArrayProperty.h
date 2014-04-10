
#pragma once

#include <vector>

#include <reflectionzeug/ValueProperty.h>
#include <reflectionzeug/ArrayPropertyInterface.h>

namespace reflectionzeug
{

/** \brief Part of the property hierarchy wrapping arbitrary n x m matrices/vectors.
 */
template <typename Type>
class ArrayProperty : public ArrayPropertyInterface<typename Type::value_type>, public ValueProperty<Type>
{
public:
    using contained_type = typename Type::value_type;
    
public:
    template <typename... Arguments>
    ArrayProperty(Arguments&&... args);
    
    virtual ~ArrayProperty() = 0;
    
    virtual void accept(AbstractPropertyVisitor * visitor, bool warn = true);

    virtual unsigned int size() const;

    virtual unsigned int columns() const;
    virtual unsigned int rows() const;

    void setDimensions(unsigned int columns, unsigned int rows);

    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);

    virtual std::vector<contained_type> toVector() const;
    virtual bool fromVector(const std::vector<contained_type> & vector);

protected:
    bool matchesArrayRegex(const std::string & string);

    virtual std::string elementRegex() const = 0;
    virtual std::string elementToString(const contained_type & element) const = 0;
    virtual contained_type elementFromString(const std::string & string) const = 0;

protected:
    unsigned int m_columns;
    unsigned int m_rows;

};

} // namespace reflectionzeug

#include "ArrayProperty.hpp"
