
#pragma once

#include <forward_list>
#include <unordered_map>
#include <propertyzeug/propertyzeug.h>
#include "Events.h"

namespace propertyzeug {
    
class AbstractProperty;
    
/** @brief
 * Manages subsriptions and notifications for events of a property.
 */

class PROPERTYZEUG_API Announcer 
{
public:
    Announcer(AbstractProperty * property);
    virtual ~Announcer();

    template <typename Object>
    void subscribe(int event, Object & object,
                   void (Object::*method_pointer)(AbstractProperty &));

    void subscribe(int event, const std::function<void(AbstractProperty &)> & functor);
    void notify(int event);

protected:
    std::forward_list<std::function<void(AbstractProperty &)>> & subscriptions(int event);

    std::unordered_map<int, std::forward_list<std::function<void(AbstractProperty &)>> *> * m_subscriptions;
    AbstractProperty * m_property;
};

template <typename Object>
void Announcer::subscribe(int event, Object & object,
    void (Object::*method_pointer)(AbstractProperty &))
{
    this->subscribe(event, std::bind(method_pointer, &object, std::placeholders::_1));
}

} // namespace