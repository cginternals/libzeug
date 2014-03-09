
#pragma once

#include <sstream>

#include <reflectionzeug/ValueProperty.h>

namespace reflectionzeug
{
    
/** \brief Part of the property hierarchy that extends the ValueProperty.
 */
template <typename Type>
class ClassProperty : public ValueProperty<Type>
{
public:
    ClassProperty(const std::string & name, const Type & value);

    ClassProperty(const std::string & name, 
                   const std::function<Type ()> & getter,
                   const std::function<void(const Type &)> & setter);
    
    template <class Object>
    ClassProperty(const std::string & name,
                   Object & object, const Type & (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(const Type &));
    
    template <class Object>
    ClassProperty(const std::string & name,
                   Object & object, Type (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(const Type &));

    template <class Object>
    ClassProperty(const std::string & name,
                   Object & object, Type (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(Type));
    
    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);

};

} // namespace reflectionzeug

#include "ClassProperty.hpp"
