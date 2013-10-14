
#include <propertyzeug/StringProperty.h>

namespace zeug {

StringProperty::StringProperty(const std::string & name,
    const std::string & value)
:   ValuePropertyTemplate<std::string>(name, value)
{
}

StringProperty::StringProperty(const std::string & name, 
    const std::function<std::string ()> & getter,
    const std::function<void(const std::string &)> & setter)
:   ValuePropertyTemplate<std::string>(name, getter, setter)
{
}

template <class Object>
StringProperty::StringProperty(const std::string & name,
    Object & object, const std::string & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const std::string &))
:   ValuePropertyTemplate<std::string>(name, object, getter_pointer, setter_pointer)
{
}
    
template <class Object>
StringProperty::StringProperty(const std::string & name,
    Object & object, std::string (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(std::string))
:   ValuePropertyTemplate<std::string>(name, object, getter_pointer, setter_pointer)
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
}
 
void StringProperty::setChoices(const std::vector<std::string> & choices)
{
    m_choices = choices;
}
 
void StringProperty::addChoice(const std::string & string)
{
    m_choices.push_back(string);
}
    
std::string StringProperty::valueAsString() const
{
    return this->value();
}
    
} // namespace

