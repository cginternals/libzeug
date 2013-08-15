
#pragma once

#include <forward_list>
#include <unordered_map>
#include <propertyzeug/propertyzeug.h>
#include "Events.h"

namespace propertyzeug {
    
class AbstractAttribute;

class PROPERTYZEUG_API Announcer 
{
public:
    Announcer(AbstractAttribute * attribute);
    virtual ~Announcer();

    template <typename Object>
    void subscribe(int event, Object * object,
                   void (Object::*method_pointer)(AbstractAttribute &));

    void subscribe(int event, const std::function<void(AbstractAttribute &)> & functor);
    void notify(int event);

protected:
    std::forward_list<std::function<void(AbstractAttribute &)>> & subscriptions(int event);

    std::unordered_map<int, std::forward_list<std::function<void(AbstractAttribute &)>> *> * m_subscriptions;
    AbstractAttribute * m_attribute;
};

template <typename Object>
void Announcer::subscribe(int event, Object * object,
    void (Object::*method_pointer)(AbstractAttribute &))
{
    this->subscribe(event, [object, method_pointer] (AbstractAttribute & attribute) {
        (object->*method_pointer)(attribute);
    });
}

} // namespace