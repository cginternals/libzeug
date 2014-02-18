
#pragma once 

#include <sstream>
#include <vector>

#include <propertyzeug/ValuePropertyTemplate.h>

namespace zeug 
{
    
/** \brief Part of the property hierarchy wrapping arbitrary n x m matrices/vectors.

    Should only be instantiated with an std::vector like container.
    The size of the container must not change, therefore it makes no sense to pass
    an empty container to the constructor.
*/
    
template <typename Vector>
class VectorProperty : public ValuePropertyTemplate<Vector>
{
public:
    VectorProperty(const std::string & name, const Vector & value);
    
    VectorProperty(const std::string & name,
                   const std::function<Vector ()> & getter,
                   const std::function<void(const Vector &)> & setter);
    
    template <class Object>
    VectorProperty(const std::string & name,
                   Object & object, const Vector & (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(const Vector &));
    
    template <class Object>
    VectorProperty(const std::string & name,
                   Object & object, Vector (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(const Vector &));

    virtual ~VectorProperty();
    
    virtual Vector value() const;
    virtual void setValue(const Vector & value);
    
    unsigned int fixedSize() const;

    unsigned int columns() const;
    unsigned int rows() const;

    void setDimensions(unsigned int columns, unsigned int rows);
    
    virtual std::string valueAsString() const;

protected:
    unsigned int m_fixedSize;
    unsigned int m_columns;
    unsigned int m_rows;
    
private:
    std::string join(const Vector & vector, const std::string & separator) const;
    
};

} // namespace zeug

#include "VectorProperty.hpp"
