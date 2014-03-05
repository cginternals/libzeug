
#pragma once

#include <reflectionzeug/Property.h>

namespace reflectionzeug
{

template <>
class Property<float> : public NumberProperty<float>
{
public:
    Property(const std::string & name, const float & value)
    :   NumberProperty<float>(name, value) {}
    
    Property(const std::string & name,
             const std::function<float ()> & getter,
             const std::function<void(const float &)> & setter)
    :   NumberProperty<float>(name, getter, setter) {}
    
    template <class Object>
    Property(const std::string & name,
             Object & object, const float & (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const float &))
    :   NumberProperty<float>(name, object, getter_pointer, setter_pointer) {}
    
    template <class Object>
    Property(const std::string & name,
             Object & object, float (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const float &))
    :   NumberProperty<float>(name, object, getter_pointer, setter_pointer) {}

};

} // namespace reflectionzeug
