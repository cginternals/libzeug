
#pragma once


#include <string>
#include <vector>

#include <reflectionzeug/property/AbstractProperty.h>
#include <reflectionzeug/property/AbstractCollection.h>


namespace reflectionzeug
{


template <typename Type>
class Property;


/**
*  @brief
*    Group of properties
*
*    A propery group is a collection of named properties while being a property itself.
*    By default, a property group owns its properties and therefore deletes them on destruction.
*    However, you can change this behaviour with setOwnsProperties().
*/
class REFLECTIONZEUG_API PropertyGroup : public AbstractCollection,
                                         public AbstractProperty
{
public:
    signalzeug::Signal<size_t, AbstractProperty *> beforeAdd;   ///< Called, before a property is added to the group
    signalzeug::Signal<size_t, AbstractProperty *> afterAdd;    ///< Called, after a property is added to the group
    signalzeug::Signal<size_t> beforeRemove;                    ///< Called, before a property is removed from the group
    signalzeug::Signal<size_t> afterRemove;                     ///< Called, after a property is removed from the group


public:
    //@{
    /**
    *  @brief
    *    Constructor
    */
    PropertyGroup();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    */
    PropertyGroup(const std::string & name);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~PropertyGroup();

    /**
    *  @brief
    *    Clear properties
    *
    *    Removes all properties from the group.
    *    If m_ownsProperties is 'true', the removed properties are deleted.
    */
    void clear();

    /**
    *  @brief
    *    Set whether the group owns its properties
    *
    *    If this is set to 'true', the property group will delete
    *    al of its properties on destruction.
    *
    *  @param[in] owns
    *    'true' if property group owns its properties, else 'false'
    */
    void setOwnsProperties(bool owns);

    /**
    *  @brief
    *    Get properties
    *
    *  @return
    *    Map of names and properties
    */
    const std::unordered_map<std::string, AbstractProperty *> & properties() const;

    /**
    *  @brief
    *    Check if property exists
    *
    *  @param[in] name
    *    Name of property
    *
    *  @return
    *    'true' if property exists, else 'false'
    */
    bool propertyExists(const std::string & name) const;
    //@}

    //@{
    /**
    *  @brief
    *    Get property
    *
    *  @param[in] path
    *    Path of property relative to the group, e.g. "Prop1", or "Sub1/Sub2/Property"
    *
    *  @return
    *    Pointer to the property, or nullptr on error
    */
    AbstractProperty * property(const std::string & path);
    const AbstractProperty * property(const std::string & path) const;
    //@}

    //@{
    /**
    *  @brief
    *    Check if group exists
    *
    *  @param[in] name
    *    Name of property group
    *
    *  @return
    *    'true' if property group exists, else 'false'
    */
    bool groupExists(const std::string & name) const;
    //@}

    //@{
    /**
    *  @brief
    *    Get property group
    *
    *  @param[in] path
    *    Path of property group relative to the group, e.g. "Sub1", or "Sub1/Sub2"
    *
    *  @return
    *    Pointer to the property group, or nullptr on error
    */
    PropertyGroup * group(const std::string & path);
    const PropertyGroup * group(const std::string & path) const;
    //@}

    //@{
    /**
    *  @brief
    *    Add property
    *
    *  @param[in] property
    *    Property
    *
    *  @return
    *    Pointer to the new property, or nullptr on error
    */
    AbstractProperty * addProperty(AbstractProperty * property);

    /**
    *  @brief
    *    Create and add property
    *
    *  @param[in] name
    *    Property name
    *  @param[in] args
    *    Property arguments
    *
    *  @return
    *    Pointer to the new property, or nullptr on error
    */
    template <typename Type, typename... Args>
    Property<Type> * addProperty(const std::string & name, Args&&... args);

    /**
    *  @brief
    *    Create and add property group
    *
    *  @param[in] name
    *    Name of property group
    *
    *  @return
    *    Pointer to the new property group, or nullptr on error
    */
    PropertyGroup * addGroup(const std::string & name);

    /**
    *  @brief
    *    Ensure that a child property path is existent
    *
    *    Returns or creates a sub-group, automatically creating all
    *    non-existent parent groups.
    *
    *  @param[in] path
    *    Path of property group relative to the group, e.g. "Sub1", or "Sub1/Sub2"
    *
    *  @return
    *    Pointer to the property group, or nullptr on error
    */
    PropertyGroup * ensureGroup(const std::string & path);

    /**
    *  @brief
    *    Remove property from group and return it
    *
    *  @param[in] name
    *    Name of property
    *
    *  @return
    *    Pointer to the property, or nullptr on error
    */
    AbstractProperty * takeProperty(const std::string & name);
    //@}

    //@{
    /**
    *  @brief
    *    Get property value
    *
    *    Get a property of the group and return its value of type Type.
    *    If the property is not of the specified type, it will return a default value.
    *
    *  @param[in] path
    *    Path of property relative to the group, e.g. "Prop1", or "Sub1/Sub2/Property"
    *
    *  @return
    *    Value of the property
    */
    template <typename Type>
    Type value(const std::string & path) const;

    /**
    *  @brief
    *    Set property value
    *
    *    Set the value of a property of the group.
    *    If the property is not of the specified type, the function will fail.
    *
    *  @param[in] path
    *    Path of property relative to the group, e.g. "Prop1", or "Sub1/Sub2/Property"
    *  @param[in] value
    *    New value
    */
    template <typename Type>
    void setValue(const std::string & path, const Type & value);
    //@}

    //@{
    /**
    *  @brief
    *    Execute callback function for each collection in this group
    *
    *  @param[in] callback
    *    Callback function
    */
    void forEachCollection(const std::function<void(AbstractCollection &)> & callback);
    void forEachCollection(const std::function<void(const AbstractCollection &)> & callback) const;
    //@}

    //@{
    /**
    *  @brief
    *    Execute callback function for each group in this group
    *
    *  @param[in] callback
    *    Callback function
    */
    void forEachGroup(const std::function<void(PropertyGroup &)> & callback);
    void forEachGroup(const std::function<void(const PropertyGroup &)> & callback) const;
    //@}

    // AbstractProperty interface
    //@{
    virtual const std::type_info & type() const override;
    virtual Variant toVariant() const override;
    virtual bool fromVariant(const Variant & value) override;
    virtual std::string toString() const override;
    virtual bool fromString(const std::string & string) override;
    virtual void accept(AbstractVisitor * visitor) override;
    //@}

    // AbstractCollection interface
    //@{
    virtual bool isEmpty() const override;
    virtual size_t count() const override;
    virtual AbstractProperty * at(size_t i) override;
    virtual const AbstractProperty * at(size_t i) const override;
    virtual int indexOf(const AbstractProperty * property) const override;
    virtual void forEach(const std::function<void(AbstractProperty &)> & callback) override;
    virtual void forEach(const std::function<void(const AbstractProperty &)> & callback) const override;
    //@}


protected:
    const AbstractProperty * findProperty(const std::vector<std::string> & path) const;
    PropertyGroup * ensureGroup(const std::vector<std::string> & path);


protected:
    std::vector<AbstractProperty *>                     m_properties;       ///< List of properties in the group
    std::unordered_map<std::string, AbstractProperty *> m_propertiesMap;    ///< Map of names and properties
    bool                                                m_ownsProperties;   ///< If 'true', the group properties are deleted on destruction
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyGroup.hpp>
