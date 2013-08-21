
#pragma once

#include <vector>
#include "BaseProperty.h"

namespace propertyzeug {

class PROPERTYZEUG_API StringProperty : public BaseProperty<std::string>
{
public:
    StringProperty(const std::string & name, const std::string & title, const std::string & value);
    
    StringProperty(const std::string & name, const std::string & title,
                  const std::function<const std::string & ()> & getter,
                  const std::function<void(const std::string &)> & setter);
    
    template <class Object>
    StringProperty(const std::string & name, const std::string & title,
                  Object & object, const std::string & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const std::string &));
    
    template <class Object>
    StringProperty(const std::string & name, const std::string & title,
                  Object & object, std::string (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(std::string));
    
    bool hasChoices() const;
    const std::vector<std::string> & choices() const;
    void clearChoices();
    void setChoices(const std::vector<std::string> & choices);
    void addChoice(const std::string & string);
    
protected:
    std::vector<std::string> m_choices;
};

} // namespace