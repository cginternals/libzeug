
#include <propertyzeug/StringAttribute.h>

namespace propertyzeug {

StringAttribute::StringAttribute(const std::string & name, const std::string & title,
    const std::string & value)
:   BaseAttribute<std::string>(name, title, value)
{
}

StringAttribute::StringAttribute(const std::string & name, const std::string & title, 
    const std::function<const std::string & ()> & getter,
    const std::function<void(const std::string &)> & setter)
:   BaseAttribute<std::string>(name, title, getter, setter)
{
}

template <class Object>
StringAttribute::StringAttribute(const std::string & name, const std::string & title,
    Object & object, const std::string & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const std::string &))
:   BaseAttribute<std::string>(name, title, object, getter_pointer, setter_pointer)
{
}
    
template <class Object>
StringAttribute::StringAttribute(const std::string & name, const std::string & title,
    Object & object, std::string (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(std::string))
:   BaseAttribute<std::string>(name, title, object, getter_pointer, setter_pointer)
{
}
     
bool StringAttribute::hasChoices() const
{
    return !m_choices.empty();
}
 
const std::vector<std::string> & StringAttribute::getChoices() const
{
    return m_choices;
}
 
void StringAttribute::clearChoices()
{
    m_choices.clear();
    this->m_announcer->notify(events::kChoicesChanged);
}
 
void StringAttribute::setChoices(const std::vector<std::string> & choices)
{
    m_choices = choices;
    this->m_announcer->notify(events::kChoicesChanged);
}
 
void StringAttribute::addChoice(const std::string & string)
{
    m_choices.push_back(string);
    this->m_announcer->notify(events::kChoicesChanged);
}
    
} // namespace

