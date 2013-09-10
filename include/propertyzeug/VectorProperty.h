
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
    
template <typename Array>
class VectorProperty : public BaseProperty<Array>
{
public:
    VectorProperty(const std::string & name, const Array & value);
    
    VectorProperty(const std::string & name,
                  const std::function<const Array & ()> & getter,
                  const std::function<void(const Array &)> & setter);
    
    template <class Object>
    VectorProperty(const std::string & name,
                  Object & object, const Array & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const Array &));
    
    template <class Object>
    VectorProperty(const std::string & name,
                  Object & object, Array (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(Array));

    virtual ~VectorProperty();
    
    virtual const Array & value() const;
    virtual void setValue(const Array & value);
    
    unsigned int fixedSize() const;

    const std::vector<unsigned int> & dimensions() const;
    void setDimensions(const std::vector<unsigned int> & dimensions);
    
    virtual std::string valueAsString() const;

protected:
    unsigned int m_fixedSize;
    std::vector<unsigned int> m_dimensions;
    
};

template <typename Array>
VectorProperty<Array>::VectorProperty(const std::string & name,
    const Array & value)
:   BaseProperty<Array>(name, value)
,   m_fixedSize(this->m_value->get().size())
,   m_dimensions({m_fixedSize})
{
    assert(m_fixedSize != 0);
}

template <typename Array>
VectorProperty<Array>::VectorProperty(const std::string & name,
    const std::function<const Array & ()> & getter,
    const std::function<void(const Array &)> & setter)
:   BaseProperty<Array>(name, getter, setter)
,   m_fixedSize(this->m_value->get().size())
,   m_dimensions({m_fixedSize})
{
    assert(m_fixedSize != 0);
}

template <typename Array>
template <class Object>
VectorProperty<Array>::VectorProperty(const std::string & name,
    Object & object, const Array & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Array &))
:   BaseProperty<Array>(name, object, getter_pointer, setter_pointer)
,   m_fixedSize(this->m_value->get().size())
,   m_dimensions({m_fixedSize})
{
    assert(m_fixedSize != 0);
}

template <typename Array>
template <class Object>
VectorProperty<Array>::VectorProperty(const std::string & name,
    Object & object, Array (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Array))
:   BaseProperty<Array>(name, object, getter_pointer, setter_pointer)
,   m_fixedSize(this->m_value->get().size())
,   m_dimensions({m_fixedSize})
{
    assert(m_fixedSize != 0);
}

template <typename Array>
VectorProperty<Array>::~VectorProperty()
{
}

template <typename Array>
const Array & VectorProperty<Array>::value() const
{
    assert(this->m_value->get().size() == m_fixedSize);
    return BaseProperty<Array>::value();
}

template <typename Array>
void VectorProperty<Array>::setValue(const Array & value)
{
    assert(value.size() == m_fixedSize);
    BaseProperty<Array>::setValue(value);
}
    
template <typename Array>
unsigned int VectorProperty<Array>::fixedSize() const
{
    return m_fixedSize;
}

template <typename Array>
const std::vector<unsigned int> & VectorProperty<Array>::dimensions() const
{
    return m_dimensions;
}

template <typename Array>
void VectorProperty<Array>::setDimensions(const std::vector<unsigned int> & dimensions)
{    
    assert(m_fixedSize == std::accumulate(dimensions.begin(), dimensions.end(), 1,
                                          [](unsigned int a, unsigned int b) {
                                              return a * b;
                                          }));
    
    m_dimensions = dimensions;
}

template <typename Array>
std::string VectorProperty<Array>::valueAsString() const
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
