
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
    ArrayProperty(const std::string & name, const Type & value);

    ArrayProperty(const std::string & name,
                   const std::function<Type ()> & getter,
                   const std::function<void(const Type &)> & setter);

    template <class Object>
    ArrayProperty(const std::string & name,
                   Object & object, const Type & (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(const Type &));

    template <class Object>
    ArrayProperty(const std::string & name,
                   Object & object, Type (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(const Type &));

    template <class Object>
    ArrayProperty(const std::string & name,
                   Object & object, Type (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(Type));
    
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
