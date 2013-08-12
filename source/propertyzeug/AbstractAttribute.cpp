
#include <propertyzeug/AbstractAttribute.h>

namespace propertyzeug {

AbstractAttribute::AbstractAttribute(std::string name, std::string title)
:   m_name(name)
,   m_title(title)
,   m_announcer(new Announcer(this))
{
}

AbstractAttribute::~AbstractAttribute()
{
    delete m_announcer;
}

std::string AbstractAttribute::name() const
{
    return m_name;
}

std::string AbstractAttribute::title() const
{
    return m_title;
}

void AbstractAttribute::setTitle(std::string title)
{
    m_title = title;
}

void AbstractAttribute::subscribe(int event, std::function<void(AbstractAttribute &)> functor)
{
    m_announcer->subscribe(event, functor);
}

} // namespace