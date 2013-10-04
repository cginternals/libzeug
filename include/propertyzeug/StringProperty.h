
#pragma once

#include <vector>

#include <signalzeug/Signal.h>

#include <propertyzeug/ValueProperty.h>

namespace zeug 
{
    
/** @brief
 * Part of the property hierarchy.
 * Manages a string and can have choices.
 */

class PROPERTYZEUG_API StringProperty : public ValueProperty<std::string>
{
public:
    StringProperty(const std::string & name, const std::string & value);
    
    StringProperty(const std::string & name,
                  const std::function<const std::string & ()> & getter,
                  const std::function<void(const std::string &)> & setter);
    
    template <class Object>
    StringProperty(const std::string & name,
                  Object & object, const std::string & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const std::string &));
    
    template <class Object>
    StringProperty(const std::string & name,
                  Object & object, std::string (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(std::string));
    
    bool hasChoices() const;
    const std::vector<std::string> & choices() const;
    void clearChoices();
    void setChoices(const std::vector<std::string> & choices);
    void addChoice(const std::string & string);
    
    virtual std::string valueAsString() const;
    
    Signal<const std::vector<std::string> &> choicesChanged;
    
protected:
    std::vector<std::string> m_choices;
};

} // namespace zeug
