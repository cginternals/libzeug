
#pragma once 

#include <sstream>
#include <set>

#include <reflectionzeug/ValuePropertyTemplate.h>

namespace reflectionzeug
{
    
/** \brief Part of the property hierarchy that should only be instantiated with an std::set like container.
 */
template <typename Set>
class SetProperty : public ValuePropertyTemplate<Set>
{
public:
    SetProperty(const std::string & name, const Set & value);
    
    SetProperty(const std::string & name,
                   const std::function<Set ()> & getter,
                   const std::function<void(const Set &)> & setter);
    
    template <class Object>
    SetProperty(const std::string & name,
                   Object & object, const Set & (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(const Set &));
    
    template <class Object>
    SetProperty(const std::string & name,
                   Object & object, Set (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(const Set &));

    virtual ~SetProperty();
    
    virtual Set value() const;
    virtual void setValue(const Set & value);
    
    virtual std::string valueAsString() const;
private:
    static std::string join(const Set & vector, const std::string & separator);
    
};

} // namespace reflectionzeug

#include "SetProperty.hpp"
