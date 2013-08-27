
#pragma once 

#include <numeric>
#include <vector>
#include "BaseProperty.h"

namespace propertyzeug {
    
template <typename Array>
class ArrayProperty : public BaseProperty<Array>
{
public:
    static const int s_noFixedSize = -1;
    
    ArrayProperty(const std::string & name,
                  const std::string & title,
                  const Array & value,
                  int fixedSize = s_noFixedSize);
    
    ArrayProperty(const std::string & name, const std:: string & title,
                  const std::function<const Array & ()> & getter,
                  const std::function<void(const Array &)> & setter,
                  int fixedSize = s_noFixedSize);
    
    template <class Object>
    ArrayProperty(const std::string & name, const std::string & title,
                  Object & object, const Array & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const Array &),
                  int fixedSize = s_noFixedSize);
    
    template <class Object>
    ArrayProperty(const std::string & name, const std::string & title,
                  Object & object, Array (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(Array),
                  int fixedSize = s_noFixedSize);

    virtual ~ArrayProperty();
    
    virtual const Array & value() const;
    virtual void setValue(const Array & value);
    
    int fixedSize() const;
    void setFixedSize(int size);

    const std::vector<unsigned int> & dimensions() const;
    void setDimensions(const std::vector<unsigned int> & dimensions);

protected:
    int m_fixedSize;
    std::vector<unsigned int> m_dimensions;
    
};

template <typename Array>
ArrayProperty<Array>::ArrayProperty(const std::string & name, const std::string & title,
    const Array & value, int fixedSize)
:   BaseProperty<Array>(name, title, value)
,   m_fixedSize(fixedSize)
{
}

template <typename Array>
ArrayProperty<Array>::ArrayProperty(const std::string & name, const std::string & title,
    const std::function<const Array & ()> & getter,
    const std::function<void(const Array &)> & setter,
    int fixedSize)
:   BaseProperty<Array>(name, title, getter, setter)
,   m_fixedSize(fixedSize)
{
}

template <typename Array>
template <class Object>
ArrayProperty<Array>::ArrayProperty(const std::string & name, const std::string & title,
    Object & object, const Array & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Array &),
    int fixedSize)
:   BaseProperty<Array>(name, title, object, getter_pointer, setter_pointer)
,   m_fixedSize(fixedSize)
{
}

template <typename Array>
template <class Object>
ArrayProperty<Array>::ArrayProperty(const std::string & name, const std::string & title,
    Object & object, Array (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Array),
    int fixedSize)
:   BaseProperty<Array>(name, title, object, getter_pointer, setter_pointer)
,   m_fixedSize(fixedSize)
{
}

template <typename Array>
ArrayProperty<Array>::~ArrayProperty()
{
}

template <typename Array>
const Array & ArrayProperty<Array>::value() const
{
    assert(this->m_value->get().size() >= m_fixedSize);
    return BaseProperty<Array>::value();
}

template <typename Array>
void ArrayProperty<Array>::setValue(const Array & value)
{
    assert(value.size() >= m_fixedSize);
    BaseProperty<Array>::setValue(value);
}
    
template <typename Array>
int ArrayProperty<Array>::fixedSize() const
{
    return m_fixedSize;
}

template <typename Array>
void ArrayProperty<Array>::setFixedSize(int size)
{
    assert(this->m_value->get().size() >= size);
    m_fixedSize = size;
    this->setDimensions(std::vector<unsigned int>(1, size));
}

template <typename Array>
const std::vector<unsigned int> & ArrayProperty<Array>::dimensions() const
{
    return m_dimensions;
}

template <typename Array>
void ArrayProperty<Array>::setDimensions(const std::vector<unsigned int> & dimensions)
{
    assert(m_fixedSize == std::accumulate(dimensions.begin(),
                                          dimensions.end(),
                                          1,
                                          [](unsigned int a, unsigned int b) {
                                              return a * b;
                                          }));
    m_dimensions = dimensions;
}

} // namespace