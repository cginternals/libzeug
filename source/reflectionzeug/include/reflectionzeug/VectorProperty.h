
#pragma once

#include <vector>

#include <reflectionzeug/ValuePropertyTemplate.h>

namespace reflectionzeug
{

/** \brief Part of the property hierarchy wrapping arbitrary n x m matrices/vectors.

    Should only be instantiated with an std::vector like container.
    The size of the container must not change, therefore it makes no sense to pass
    an empty container to the constructor.
*/

template <typename Type>
class VectorProperty : public ValuePropertyTemplate<std::vector<Type>>
{
public:
    VectorProperty(const std::string & name, const std::vector<Type> & value);

    VectorProperty(const std::string & name,
                   const std::function<std::vector<Type> ()> & getter,
                   const std::function<void(const std::vector<Type> &)> & setter);

    template <class Object>
    VectorProperty(const std::string & name,
                   Object & object, const std::vector<Type> & (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(const std::vector<Type> &));

    template <class Object>
    VectorProperty(const std::string & name,
                   Object & object, std::vector<Type> (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(const std::vector<Type> &));

    template <class Object>
    VectorProperty(const std::string & name,
                   Object & object, std::vector<Type> (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(std::vector<Type>));

    virtual ~VectorProperty();

    virtual std::vector<Type> value() const;
    virtual void setValue(const std::vector<Type> & value);

    unsigned int fixedSize() const;

    unsigned int columns() const;
    unsigned int rows() const;

    void setDimensions(unsigned int columns, unsigned int rows);

    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);

protected:
    bool matchesVectorRegex(const std::string & string);

    virtual std::string elementRegex() = 0;
    virtual std::string elementToString(const Type * element) = 0;
    virtual Type elementFromString(const std::string & string) = 0;

protected:
    unsigned int m_fixedSize;
    unsigned int m_columns;
    unsigned int m_rows;

};

} // namespace reflectionzeug

#include "VectorProperty.hpp"
