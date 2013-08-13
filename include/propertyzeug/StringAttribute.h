
#pragma once

#include <vector>
#include "BaseAttribute.h"

namespace propertyzeug {

class PROPERTYZEUG_API StringAttribute : public BaseAttribute<std::string>
{
public:
    StringAttribute(const std::string & name, const std::string & title, const std::string & value);
    
    StringAttribute(const std::string & name, const std::string & title,
                  const std::function<const std::string & ()> & getter,
                  const std::function<void(const std::string &)> & setter);
    
    template <class Object>
    StringAttribute(const std::string & name, const std::string & title,
                  Object & object, const std::string & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const std::string &));
    
    template <class Object>
    StringAttribute(const std::string & name, const std::string & title,
                  Object & object, std::string (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(std::string));
    
    bool hasChoices() const;
    const std::vector<std::string> & getChoices() const;
    void clearChoices();
    void setChoices(const std::vector<std::string> & choices);
    void addChoice(const std::string & string);
    
protected:
    std::vector<std::string> m_choices;
};

} // namespace