
#include <propertyzeug/StringProperty.h>

namespace propertyzeug {

StringProperty::StringProperty(const std::string & name, const std::string & title,
    const std::string & value)
:   BaseProperty<std::string>(name, title, value)
{
}

StringProperty::StringProperty(const std::string & name, const std::string & title, 
    const std::function<const std::string & ()> & getter,
    const std::function<void(const std::string &)> & setter)
:   BaseProperty<std::string>(name, title, getter, setter)
{
}

template <class Object>
StringProperty::StringProperty(const std::string & name, const std::string & title,
    Object & object, const std::string & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const std::string &))
:   BaseProperty<std::string>(name, title, object, getter_pointer, setter_pointer)
{
}
    
template <class Object>
StringProperty::StringProperty(const std::string & name, const std::string & title,
    Object & object, std::string (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(std::string))
:   BaseProperty<std::string>(name, title, object, getter_pointer, setter_pointer)
{
}
     
bool StringProperty::hasChoices() const
{
    return !m_choices.empty();
}
 
const std::vector<std::string> & StringProperty::choices() const
{
    return m_choices;
}
 
void StringProperty::clearChoices()
{
    m_choices.clear();
    this->m_announcer.notify(events::kChoicesChanged);
}
 
void StringProperty::setChoices(const std::vector<std::string> & choices)
{
    m_choices = choices;
    this->m_announcer.notify(events::kChoicesChanged);
}
 
void StringProperty::addChoice(const std::string & string)
{
    m_choices.push_back(string);
    this->m_announcer.notify(events::kChoicesChanged);
}
    
} // namespace

