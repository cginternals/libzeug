
#pragma once

#include <functional>

#include <reflectionzeug/AbstractValue.h>

namespace reflectionzeug
{
    
/** \brief Provides access to a value by accessors.
 */
template <typename Type>
class AccessorValue : public AbstractValue<Type>
{
public:
    AccessorValue(std::function<Type ()> getter,
                  std::function<void(const Type &)> setter);
    
    template <class Object>
    AccessorValue(Object & object,
                  const Type & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const Type &));
    
    template <class Object>
    AccessorValue(Object & object,
                  Type (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const Type &));

    template <class Object>
    AccessorValue(Object & object,
                  Type (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(Type));
  
    virtual ~AccessorValue();

    virtual Type get() const;
    virtual void set(const Type & value);

protected:
    std::function<Type ()> m_getter;
    std::function<void(const Type &)> m_setter;
};

} // namespace reflectionzeug

#include "AccessorValue.hpp"
