
#pragma once

#include <forward_list>
#include <unordered_map>
#include <propertyzeug/propertyzeug.h>
#include "AbstractProperty.h"
#include "Property.h"

namespace propertyzeug {

class PROPERTYZEUG_API PropertyGroup : public AbstractProperty
{
public:
    PropertyGroup(std::string name, std::string title);
    virtual ~PropertyGroup();
    
    bool addProperty(AbstractProperty * property);
    
    template <typename Type>
    bool addProperty(const std::string & name,
                     const std::string & title,
                     const Type & value);
    
    template <typename Type>
    bool addProperty(const std::string & name, const std::string & title,
                 const std::function<const Type & ()> & getter,
                 const std::function<void(const Type &)> & setter);
    
    template <typename Type, class Object>
    bool addProperty(const std::string & name, const std::string & title,
                 Object & object, const Type & (Object::*getter_pointer)() const,
                 void (Object::*setter_pointer)(const Type &));
    
    template <typename Type, class Object>
    bool addProperty(const std::string & name, const std::string & title,
                 Object & object, Type (Object::*getter_pointer)() const,
                 void (Object::*setter_pointer)(Type));
    

    AbstractProperty & property(const std::string & name);

    template <typename Type>
    Property<Type> & property(const std::string & name);
    

    template <typename Type>
    const Type & value(const std::string & name) const;
    
    template <typename Type>
    bool setValue(const std::string & name, const Type & value);

    
    bool propertyExists(const std::string & name) const;
    
    AbstractProperty * replaceProperty(const std::string & name,
                                       AbstractProperty * property);

    bool insertPropertyAfter(const std::string & name, 
                             AbstractProperty * property);

    bool removeProperty(AbstractProperty * property);
    
    AbstractProperty * obtainProperty(const std::string & name);
    
    
protected:
    std::forward_list<AbstractProperty *> m_properties;
    std::unordered_map<std::string, AbstractProperty *> m_propertiesMap;
};

} // namespace