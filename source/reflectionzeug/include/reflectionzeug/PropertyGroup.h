
#pragma once


#include <string>
#include <vector>

#include <reflectionzeug/type/AbstractValue.h>
#include <reflectionzeug/type/AbstractCollection.h>


namespace reflectionzeug
{


template <typename Type>
class Property;


/**
*  @brief
*    Group of properties
*/
class REFLECTIONZEUG_API PropertyGroup : public AbstractCollection,
                                         public AbstractValue
{
public:
    signalzeug::Signal<size_t, AbstractValue *> beforeAdd;
    signalzeug::Signal<size_t, AbstractValue *> afterAdd;
    signalzeug::Signal<size_t> beforeRemove;
    signalzeug::Signal<size_t> afterRemove;


public:
    PropertyGroup();
    PropertyGroup(const std::string & name);
    virtual ~PropertyGroup();

    const std::unordered_map<std::string, AbstractValue *> & properties() const;

    AbstractValue * property(const std::string & path);

    const AbstractValue * property(const std::string & path) const;

    template <typename Type>
    const Property<Type> * property(const std::string & path) const;

    template <typename Type>
    Property<Type> * property(const std::string & path);

    AbstractValue * addProperty(AbstractValue * property);

    template <typename Type, typename... Args>
    Property<Type> * addProperty(const std::string & name, Args&&... args);

    PropertyGroup * group(const std::string & path);

    const PropertyGroup * group(const std::string & path) const;

    PropertyGroup * addGroup(const std::string & name);

    PropertyGroup * ensureGroup(const std::string & path);

    template <typename Type>
    Type value(const std::string & path) const;

    template <typename Type>
    void setValue(const std::string & path, const Type & value);

    // AbstractValue interface
    virtual const std::type_info & type() const override;
    virtual Variant toVariant() const override;
    virtual bool fromVariant(const Variant & value) override;

    // AbstractCollection interface
    virtual bool isEmpty() const override;
    virtual size_t count() const override;
    virtual AbstractValue * at(size_t i) override;
    virtual const AbstractValue * at(size_t i) const override;
    virtual int indexOf(const AbstractValue * value) const override;
    virtual void forEach(const std::function<void(AbstractValue &)> & callback) override;
    virtual void forEach(const std::function<void(const AbstractValue &)> & callback) const override;

    /**
     * Removes the property with the given name from the group and returns it.
     */
    AbstractValue * takeProperty(const std::string & name);

    /**
     * Removes all properties from the group. Deletes them if it owns them.
     */
    void clear();

    /**
     * Sets whether the group deletes its properties on destruction or not.
     */
    void setOwnsProperties(bool owns);

    bool propertyExists(const std::string & name) const;
    bool groupExists(const std::string & name) const;

    void forEachCollection(const std::function<void(AbstractCollection &)> & callback);
    void forEachCollection(const std::function<void(const AbstractCollection &)> & callback) const;

    void forEachGroup(const std::function<void(PropertyGroup &)> & callback);
    void forEachGroup(const std::function<void(const PropertyGroup &)> & callback) const;

    virtual void accept(AbstractVisitor * visitor) override;


protected:
    const AbstractValue * findProperty(const std::vector<std::string> & path) const;
    PropertyGroup * ensureGroup(const std::vector<std::string> & path);


protected:
    std::vector<AbstractValue *> m_properties;
    std::unordered_map<std::string, AbstractValue *> m_propertiesMap;
    bool m_ownsProperties;
};


} // namespace reflectionzeug


#include <reflectionzeug/PropertyGroup.hpp>
