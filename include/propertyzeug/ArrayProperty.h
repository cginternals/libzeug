
#pragma once 

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
class ArrayProperty : public BaseProperty<Array>
{
public:
    ArrayProperty(const std::string & name,
                  const std::string & title,
                  const Array & value);
    
    ArrayProperty(const std::string & name, const std:: string & title,
                  const std::function<const Array & ()> & getter,
                  const std::function<void(const Array &)> & setter);
    
    template <class Object>
    ArrayProperty(const std::string & name, const std::string & title,
                  Object & object, const Array & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const Array &));
    
    template <class Object>
    ArrayProperty(const std::string & name, const std::string & title,
                  Object & object, Array (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(Array));

    virtual ~ArrayProperty();
    
    virtual const Array & value() const;
    virtual void setValue(const Array & value);
    
    unsigned int fixedSize() const;

    const std::vector<unsigned int> & dimensions() const;
    void setDimensions(const std::vector<unsigned int> & dimensions);

protected:
    unsigned int m_fixedSize;
    std::vector<unsigned int> m_dimensions;
    
};

template <typename Array>
ArrayProperty<Array>::ArrayProperty(const std::string & name, const std::string & title,
    const Array & value)
:   BaseProperty<Array>(name, title, value)
,   m_fixedSize(this->m_value->get().size())
{
}

template <typename Array>
ArrayProperty<Array>::ArrayProperty(const std::string & name, const std::string & title,
    const std::function<const Array & ()> & getter,
    const std::function<void(const Array &)> & setter)
:   BaseProperty<Array>(name, title, getter, setter)
,   m_fixedSize(this->m_value->get().size())
{
}

template <typename Array>
template <class Object>
ArrayProperty<Array>::ArrayProperty(const std::string & name, const std::string & title,
    Object & object, const Array & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Array &))
:   BaseProperty<Array>(name, title, object, getter_pointer, setter_pointer)
,   m_fixedSize(this->m_value->get().size())
{
}

template <typename Array>
template <class Object>
ArrayProperty<Array>::ArrayProperty(const std::string & name, const std::string & title,
    Object & object, Array (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Array))
:   BaseProperty<Array>(name, title, object, getter_pointer, setter_pointer)
,   m_fixedSize(this->m_value->get().size())
{
}

template <typename Array>
ArrayProperty<Array>::~ArrayProperty()
{
}

template <typename Array>
const Array & ArrayProperty<Array>::value() const
{
    assert(this->m_value->get().size() == m_fixedSize);
    return BaseProperty<Array>::value();
}

template <typename Array>
void ArrayProperty<Array>::setValue(const Array & value)
{
    assert(value.size() == m_fixedSize);
    BaseProperty<Array>::setValue(value);
}
    
template <typename Array>
unsigned int ArrayProperty<Array>::fixedSize() const
{
    return m_fixedSize;
}

template <typename Array>
const std::vector<unsigned int> & ArrayProperty<Array>::dimensions() const
{
    return m_dimensions;
}

template <typename Array>
void ArrayProperty<Array>::setDimensions(const std::vector<unsigned int> & dimensions)
{    
    assert(m_fixedSize == std::accumulate(dimensions.begin(), dimensions.end(), 1,
                                          [](unsigned int a, unsigned int b) {
                                              return a * b;
                                          }));
    
    m_dimensions = dimensions;
}

} // namespace