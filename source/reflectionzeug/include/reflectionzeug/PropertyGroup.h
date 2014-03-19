
#pragma once

#include <assert.h>
#include <vector>
#include <unordered_map>

#include <reflectionzeug/reflectionzeug.h>

#include <reflectionzeug/Property.h>

namespace reflectionzeug
{
    
/** \brief Part of the Property Hierarchy that manages properties while being a property itself.
*/
class REFLECTIONZEUG_API PropertyGroup : public AbstractProperty
{
public:
    PropertyGroup(const std::string & name);
    virtual ~PropertyGroup();
    
    virtual bool isGroup() const;
    
    /** \name Property Adding
        \brief Methods for adding properties.
     */
    /** \{ */
    
    bool addProperty(AbstractProperty * property);
    
    template <typename Type>
    Property<Type> * addProperty(const std::string & name,
                                 const Type & value);
    
    template <typename Type>
    Property<Type> * addProperty(const std::string & name,
                                 const std::function<Type ()> & getter,
                                 const std::function<void(const Type &)> & setter);
    
    template <typename Type, class Object>
    Property<Type> * addProperty(const std::string & name,
                                 Object & object, 
                                 const Type & (Object::*getter_pointer)() const,
                                 void (Object::*setter_pointer)(const Type &));
    
    template <typename Type, class Object>
    Property<Type> * addProperty(const std::string & name,
                                 Object & object, 
                                 Type (Object::*getter_pointer)() const,
                                 void (Object::*setter_pointer)(const Type &));
    
    template <typename Type, class Object>
    Property<Type> * addProperty(const std::string & name,
                                 Object & object,
                                 Type (Object::*getter_pointer)() const,
                                 void (Object::*setter_pointer)(Type));
    
    PropertyGroup * addGroup(const std::string & name);

    bool addGroup(PropertyGroup * group);

    /** \} */
    
    /** \name Property Accessing
        \brief Methods accessing properties, subgroups and values.
        Acces Properties in the hierachy with the separater '/'
    */
    /** \{ */
    
    AbstractProperty * property(const std::string & path);
    const AbstractProperty * property(const std::string & path) const;

    template <typename Type>
    Property<Type> * property(const std::string & path);
    
    template <typename Type>
    const Property<Type> * property(const std::string & path) const;

    PropertyGroup * group(const std::string & path);
    const PropertyGroup * group(const std::string & path) const;

    template <typename Type>
    Type value(const std::string & path) const;
    
    template <typename Type>
    void setValue(const std::string & path, const Type & value);
    
    AbstractProperty * property(unsigned int index);
    const AbstractProperty * property(unsigned int index) const;
    
    /** \} */

    /** \name Properties
        \brief Methods for manipulating properties
    */
    /** \{ */

    bool propertyExists(const std::string & name) const;
    bool groupExists(const std::string & name) const;
    
    bool hasProperties() const;
    unsigned int propertyCount() const;
    int indexOfProperty(const std::string & name) const;

    AbstractProperty * obtainProperty(const std::string & name);
    bool removeProperty(AbstractProperty * property);

    /** \} */
    
    /** \name Property Iterators
        \brief Methods for property iteration
     */
    /** \{ */
    
    void forEachProperty(const std::function<void(AbstractProperty &)> functor);
    void forEachProperty(const std::function<void(const AbstractProperty &)> functor) const;
    
    void forEachValuePropertyInterface(const std::function<void(ValuePropertyInterface &)> functor);
    void forEachValuePropertyInterface(const std::function<void(const ValuePropertyInterface &)> functor) const;
    
    void forEachSubGroup(const std::function<void(PropertyGroup &)> functor);
    void forEachSubGroup(const std::function<void(const PropertyGroup &)> functor) const;
    
    /** \} */
    
protected:
    std::vector<AbstractProperty *> m_properties;
    std::unordered_map<std::string, AbstractProperty *> m_propertiesMap;
    
private:
    AbstractProperty * findProperty(const std::string & path);
    const AbstractProperty * findProperty(const std::string & path) const;
};

} // namespace reflectionzeug

#include "PropertyGroup.hpp" 
