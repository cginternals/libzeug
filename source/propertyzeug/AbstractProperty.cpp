
#include <propertyzeug/AbstractProperty.h>

namespace propertyzeug {

AbstractProperty::AbstractProperty(std::string name, std::string title)
:   m_name(name)
,   m_title(title)
,   m_announcer(this)
{
}

AbstractProperty::~AbstractProperty()
{
}

std::string AbstractProperty::name() const
{
    return m_name;
}

std::string AbstractProperty::title() const
{
    return m_title;
}

void AbstractProperty::setTitle(std::string title)
{
    m_title = title;
    m_announcer.notify(events::kTitleChanged);
}

void AbstractProperty::subscribe(int event, std::function<void(AbstractProperty &)> functor)
{
    m_announcer.subscribe(event, functor);
}

} // namespace