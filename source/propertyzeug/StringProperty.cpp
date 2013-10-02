
#include <propertyzeug/StringProperty.h>

namespace propertyzeug {

StringProperty::StringProperty(const std::string & name,
    const std::string & value)
:   ValueProperty<std::string>(name, value)
{
}

StringProperty::StringProperty(const std::string & name, 
    const std::function<const std::string & ()> & getter,
    const std::function<void(const std::string &)> & setter)
:   ValueProperty<std::string>(name, getter, setter)
{
}

template <class Object>
StringProperty::StringProperty(const std::string & name,
    Object & object, const std::string & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const std::string &))
:   ValueProperty<std::string>(name, object, getter_pointer, setter_pointer)
{
}
    
template <class Object>
StringProperty::StringProperty(const std::string & name,
    Object & object, std::string (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(std::string))
:   ValueProperty<std::string>(name, object, getter_pointer, setter_pointer)
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
    this->choicesChanged(m_choices);
}
 
void StringProperty::setChoices(const std::vector<std::string> & choices)
{
    m_choices = choices;
    this->choicesChanged(m_choices);
}
 
void StringProperty::addChoice(const std::string & string)
{
    m_choices.push_back(string);
    this->choicesChanged(m_choices);
}
    
std::string StringProperty::valueAsString() const
{
    return this->value();
}
    
} // namespace

