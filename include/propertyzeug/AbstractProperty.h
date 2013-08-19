
#pragma once

#include <assert.h>
#include <string>
#include <iostream>
#include <propertyzeug/propertyzeug.h>
#include "Announcer.h"

namespace propertyzeug {
    
class Announcer;

class PROPERTYZEUG_API AbstractProperty 
{
public:
    AbstractProperty(const std::string & name, const std::string & title);
    virtual ~AbstractProperty();

    // virtual void accept(AbstractPropertyVisitor & visitor) = 0;

    const std::string & name() const;
    const std::string & title() const;
    void setTitle(const std::string & title);

    template <class Property>
    Property * to();

    template <typename Object>
    void subscribe(int event, Object & object,
                   void (Object::*method_pointer)(AbstractProperty &));

    void subscribe(int event, const std::function<void(AbstractProperty &)> & functor);

protected:
    std::string m_name;
    std::string m_title;
    Announcer m_announcer;
};

template <class Property>
Property * AbstractProperty::to()
{
    Property * property = dynamic_cast<Property *>(this);
    assert(property);
    return property;
}

template <typename Object>
void AbstractProperty::subscribe(int event, Object & object,
    void (Object::*method_pointer)(AbstractProperty &))
{
    m_announcer.subscribe(event, object, method_pointer);
}

} // namespace