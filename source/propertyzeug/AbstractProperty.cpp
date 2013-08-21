
#include <propertyzeug/AbstractProperty.h>

namespace propertyzeug {

AbstractProperty::AbstractProperty(const std::string & name,
    const std::string & title)
:   m_name(name)
,   m_title(title)
,   m_announcer(this)
{
}

AbstractProperty::~AbstractProperty()
{
}

const std::string & AbstractProperty::name() const
{
    return m_name;
}

const std::string & AbstractProperty::title() const
{
    return m_title;
}

void AbstractProperty::setTitle(const std::string & title)
{
    m_title = title;
    m_announcer.notify(events::kTitleChanged);
}

void AbstractProperty::subscribe(int event, const std::function<void(AbstractProperty &)> & functor)
{
    m_announcer.subscribe(event, functor);
}
    
bool AbstractProperty::isGroup() const
{
    return false;
}

} // namespace