
#include <reflectionzeug/StringProperty.h>

namespace reflectionzeug
{

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
    this->choicesChanged(m_choices);
}
 
const std::vector<std::string> & StringProperty::choices() const
{
    return m_choices;
}
 
void StringProperty::setChoices(const std::vector<std::string> & choices)
{
    m_choices = choices;
    this->choicesChanged(m_choices);
}
    
void StringProperty::clearChoices()
{
    m_choices.clear();
    this->choicesChanged(m_choices);
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
