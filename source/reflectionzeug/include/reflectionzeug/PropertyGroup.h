
#pragma once

#include <vector>
#include <unordered_map>

#include <reflectionzeug/reflectionzeug.h>
#include <reflectionzeug/property_declaration.h>
#include <reflectionzeug/AbstractPropertyCollection.h>

namespace reflectionzeug
{
    
class AbstractValueProperty;
    
/** \brief Part of the Property Hierarchy that manages properties while being a property itself.
*/
class REFLECTIONZEUG_API PropertyGroup : public AbstractPropertyCollection
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
    Property<Type> * addProperty(const std::string & name, const Type & value);

    template <typename Type, typename... Args>
    Property<Type> * addProperty(const std::string & name, Args&&... args);
    
    PropertyGroup * addGroup(const std::string & name);

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
    
    virtual AbstractProperty * at(size_t index);
    virtual const AbstractProperty * at(size_t index) const;
    
    /** \} */

    /** \name Properties
        \brief Methods for manipulating properties
    */
    /** \{ */

    bool propertyExists(const std::string & name) const;
    bool groupExists(const std::string & name) const;
    
    virtual bool isEmpty() const;
    virtual size_t count() const;
    virtual int indexOf(const AbstractProperty * property) const;

    AbstractProperty * takeProperty(const std::string & name);
    bool removeProperty(AbstractProperty * property);

    /** \} */
    
    /** \name Property Iterators
        \brief Methods for property iteration
     */
    /** \{ */
    
    void forEach(const std::function<void(AbstractProperty &)> & functor);
    void forEach(const std::function<void(const AbstractProperty &)> & functor) const;
    
    void forEachValue(const std::function<void(AbstractValueProperty &)> & functor);
    void forEachValue(const std::function<void(const AbstractValueProperty &)> & functor) const;
    
    void forEachCollection(const std::function<void(AbstractPropertyCollection &)> & functor);
    void forEachCollection(const std::function<void(const AbstractPropertyCollection &)> & functor) const;

    void forEachGroup(const std::function<void(PropertyGroup &)> & functor);
    void forEachGroup(const std::function<void(const PropertyGroup &)> & functor) const;
    
    /** \} */
    
private:
    AbstractProperty * findProperty(const std::string & path);
    const AbstractProperty * findProperty(const std::string & path) const;
    
private:
    std::vector<AbstractProperty *> m_properties;
    std::unordered_map<std::string, AbstractProperty *> m_propertiesMap;
};

} // namespace reflectionzeug

#include "PropertyGroup.hpp" 
