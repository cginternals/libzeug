
#pragma once

#include <typeinfo>
#include <string>
#include <iostream>
#include <propertyzeug/propertyzeug.h>
#include "announcer.h"

namespace propertyzeug {
    
class Announcer;

class PROPERTYZEUG_API AbstractAttribute 
{
public:
    AbstractAttribute(std::string name, std::string title);
    virtual ~AbstractAttribute();

    // virtual void accept(AbstractAttributeVisitor & visitor) = 0;

    std::string name() const;
    std::string title() const;
    void setTitle(std::string title);

    template <class Property>
    Property * to();

    template <typename Object>
    void subscribe(int event, Object * object,
        void (Object::*method_pointer)(AbstractAttribute &));

    void subscribe(int event, std::function<void(AbstractAttribute &)> functor);

protected:
    Announcer & announcer() const;

    std::string m_name;
    std::string m_title;
    Announcer * m_announcer;
};

template <class Attribute>
Attribute * AbstractAttribute::to()
{
    Attribute * attribute = dynamic_cast<Attribute *>(this);
    if (!attribute)
        std::cerr << "Requested Attribute " << this->name()
            << " is not of Type " << typeid(Attribute).name();
    return attribute;
}

template <typename Object>
void AbstractAttribute::subscribe(int event, Object * object,
    void (Object::*method_pointer)(AbstractAttribute &))
{
    m_announcer->subscribe(event, object, method_pointer);
}

} // namespace