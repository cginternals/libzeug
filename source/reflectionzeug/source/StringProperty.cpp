
#include <reflectionzeug/StringProperty.h>

namespace reflectionzeug
{

StringProperty::StringProperty(const std::string & value)
:   ValueProperty<std::string>(value)
{
}

StringProperty::StringProperty( 
    const std::function<std::string ()> & getter,
    const std::function<void(const std::string &)> & setter)
:   ValueProperty<std::string>(getter, setter)
{
}

StringProperty::~StringProperty()
{
}
    
bool StringProperty::hasChoices() const
{
    return !m_choices.empty();
}
 
void StringProperty::addChoice(const std::string & string)
{
    m_choices.push_back(string);
}
 
const std::vector<std::string> & StringProperty::choices() const
{
    return m_choices;
}
 
void StringProperty::setChoices(const std::vector<std::string> & choices)
{
    m_choices = choices;
}
    
void StringProperty::clearChoices()
{
    m_choices.clear();
}
 
std::string StringProperty::toString() const
{
    return this->value();
}

bool StringProperty::fromString(const std::string & string)
{
    this->setValue(string);
    return true;
}
    
} // namespace reflectionzeug
