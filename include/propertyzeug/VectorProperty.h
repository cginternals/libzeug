
#pragma once 

#include <sstream>
#include <numeric>
#include <vector>
#include "BaseProperty.h"

namespace propertyzeug {
    
/** @brief
 * Part of the property hierarchy.
 * Should only be instantiated with an std::vector like container.
 * The size of the container must not change, therefore it makes no sense to pass
 * an empty container to the constructor.
 */
    
template <typename Vector>
class VectorProperty : public BaseProperty<Vector>
{
public:
    VectorProperty(const std::string & name, const Vector & value);
    
    VectorProperty(const std::string & name,
                  const std::function<const Vector & ()> & getter,
                  const std::function<void(const Vector &)> & setter);
    
    template <class Object>
    VectorProperty(const std::string & name,
                  Object & object, const Vector & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const Vector &));
    
    template <class Object>
    VectorProperty(const std::string & name,
                  Object & object, Vector (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(Vector));

    virtual ~VectorProperty();
    
    virtual const Vector & value() const;
    virtual void setValue(const Vector & value);
    
    unsigned int fixedSize() const;

    const std::vector<unsigned int> & dimensions() const;
    void setDimensions(const std::vector<unsigned int> & dimensions);
    
    virtual std::string valueAsString() const;

protected:
    unsigned int m_fixedSize;
    std::vector<unsigned int> m_dimensions;
    
};

template <typename Vector>
VectorProperty<Vector>::VectorProperty(const std::string & name,
    const Vector & value)
:   BaseProperty<Vector>(name, value)
,   m_fixedSize(this->m_value->get().size())
,   m_dimensions({m_fixedSize})
{
    assert(m_fixedSize != 0);
}

template <typename Vector>
VectorProperty<Vector>::VectorProperty(const std::string & name,
    const std::function<const Vector & ()> & getter,
    const std::function<void(const Vector &)> & setter)
:   BaseProperty<Vector>(name, getter, setter)
,   m_fixedSize(this->m_value->get().size())
,   m_dimensions({m_fixedSize})
{
    assert(m_fixedSize != 0);
}

template <typename Vector>
template <class Object>
VectorProperty<Vector>::VectorProperty(const std::string & name,
    Object & object, const Vector & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Vector &))
:   BaseProperty<Vector>(name, object, getter_pointer, setter_pointer)
,   m_fixedSize(this->m_value->get().size())
,   m_dimensions({m_fixedSize})
{
    assert(m_fixedSize != 0);
}

template <typename Vector>
template <class Object>
VectorProperty<Vector>::VectorProperty(const std::string & name,
    Object & object, Vector (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Vector))
:   BaseProperty<Vector>(name, object, getter_pointer, setter_pointer)
,   m_fixedSize(this->m_value->get().size())
,   m_dimensions({m_fixedSize})
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
    return BaseProperty<Vector>::value();
}

template <typename Vector>
void VectorProperty<Vector>::setValue(const Vector & value)
{
    assert(value.size() == m_fixedSize);
    BaseProperty<Vector>::setValue(value);
}
    
template <typename Vector>
unsigned int VectorProperty<Vector>::fixedSize() const
{
    return m_fixedSize;
}

template <typename Vector>
const std::vector<unsigned int> & VectorProperty<Vector>::dimensions() const
{
    return m_dimensions;
}

template <typename Vector>
void VectorProperty<Vector>::setDimensions(const std::vector<unsigned int> & dimensions)
{    
    assert(m_fixedSize == std::accumulate(dimensions.begin(), dimensions.end(), 1,
                                          [](unsigned int a, unsigned int b) {
                                              return a * b;
                                          }));
    
    m_dimensions = dimensions;
}

template <typename Vector>
std::string VectorProperty<Vector>::valueAsString() const
{
    std::stringstream stream;
    stream << "(";
    for(auto e = this->value().begin(); e < --this->value().end(); e++) {
        stream << *e << ",";
    }
    stream << this->value().back();
    stream << ")";
    
    return stream.str();
}

} // namespace
