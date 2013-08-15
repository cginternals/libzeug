
#pragma once

#include <typeinfo>
#include <string>
#include <iostream>
#include <propertyzeug/propertyzeug.h>
#include "Announcer.h"

namespace propertyzeug {
    
class Announcer;

class PROPERTYZEUG_API AbstractProperty 
{
public:
    AbstractProperty(std::string name, std::string title);
    virtual ~AbstractProperty();

    // virtual void accept(AbstractPropertyVisitor & visitor) = 0;

    std::string name() const;
    std::string title() const;
    void setTitle(std::string title);

    template <class Property>
    Property * to();

    template <typename Object>
    void subscribe(int event, Object * object,
                   void (Object::*method_pointer)(AbstractProperty &));

    void subscribe(int event, std::function<void(AbstractProperty &)> functor);

protected:
    std::string m_name;
    std::string m_title;
    Announcer m_announcer;
};

template <class Property>
Property * AbstractProperty::to()
{
    Property * attribute = dynamic_cast<Property *>(this);
    if (!attribute)
        std::cerr << "Requested Property " << this->name()
            << " is not of Type " << typeid(Property).name();
    return attribute;
}

template <typename Object>
void AbstractProperty::subscribe(int event, Object * object,
    void (Object::*method_pointer)(AbstractProperty &))
{
    m_announcer.subscribe(event, object, method_pointer);
}

} // namespace