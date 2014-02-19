
#pragma once

#include <vector>

#include <signalzeug/Signal.h>

#include <reflectionzeug/reflectionzeug.h>
#include <reflectionzeug/ValuePropertyTemplate.h>

namespace reflectionzeug
{
    
/** \brief Part of the property hierarchy that manages a string and can have choices.
 */
class REFLECTIONZEUG_API StringProperty : public ValuePropertyTemplate<std::string>
{
public:
    StringProperty(const std::string & name, const std::string & value);
    
    StringProperty(const std::string & name,
                   const std::function<std::string ()> & getter,
                   const std::function<void(const std::string &)> & setter);
    
    template <class Object>
    StringProperty(const std::string & name,
                   Object & object, const std::string & (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(const std::string &));
    
    template <class Object>
    StringProperty(const std::string & name,
                   Object & object, std::string (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(const std::string &));
    
    bool hasChoices() const;
    const std::vector<std::string> & choices() const;
    void clearChoices();
    void setChoices(const std::vector<std::string> & choices);
    void addChoice(const std::string & string);
    
    virtual std::string valueAsString() const;
    
    signalzeug::Signal<const std::vector<std::string> &> choicesChanged;
    
protected:
    std::vector<std::string> m_choices;
};

template <class Object>
StringProperty::StringProperty(const std::string & name,
    Object & object
,   const std::string & (Object::*getter_pointer)() const
,   void (Object::*setter_pointer)(const std::string &))
:   ValuePropertyTemplate<std::string>(name, object, getter_pointer, setter_pointer)
{
}
    
template <class Object>
StringProperty::StringProperty(const std::string & name,
    Object & object, std::string (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const std::string &))
:   ValuePropertyTemplate<std::string>(name, object, getter_pointer, setter_pointer)
{
}

} // namespace reflectionzeug
