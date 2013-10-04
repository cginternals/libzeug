
#include <propertyzeug/Announcer.h>
#include <propertyzeug/AbstractProperty.h>

namespace zeug {

Announcer::Announcer(AbstractProperty * property)
:   m_subscriptions(new std::unordered_map<int, 
        std::forward_list<std::function<void(AbstractProperty &)>> *>())
,   m_property(property)
{
}

Announcer::~Announcer()
{
    for (auto pair : *m_subscriptions)
        delete std::get<1>(pair);
    delete m_subscriptions;
}

void Announcer::subscribe(int event, const std::function<void(AbstractProperty &)> & functor)
{
    this->subscriptions(event).push_front(functor);
}

void Announcer::notify(int event)
{
    for (std::function<void(AbstractProperty &)> functor : this->subscriptions(event))
        functor(*m_property);
}

std::forward_list<std::function<void(AbstractProperty &)>> & Announcer::subscriptions(int event)
{
    if (m_subscriptions->find(event) == m_subscriptions->end()) {
        auto list = new std::forward_list<std::function<void(AbstractProperty &)>>();
        m_subscriptions->insert(std::make_pair(event, list));
    }
    
    return *m_subscriptions->at(event);
}

}
