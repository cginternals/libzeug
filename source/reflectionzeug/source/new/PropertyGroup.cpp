
#include <cassert>
#include <algorithm>

#include <reflectionzeug/new/PropertyGroup.h>
#include <reflectionzeug/new/AbstractProperty.h>
#include <reflectionzeug/new/AbstractVisitor.h>
#include <reflectionzeug/util.h>


namespace reflectionzeug
{


PropertyGroup2::PropertyGroup2(const std::string & name)
: m_name(name)
, m_ownsProperties(true)
{
}

PropertyGroup2::PropertyGroup2()
: m_ownsProperties(true)
{
}

PropertyGroup2::~PropertyGroup2()
{
    // Delete owned properties
    if (m_ownsProperties)
    {
        for (AbstractProperty2 * property : m_properties)
        {
            delete property;
        }
    }
}

std::string PropertyGroup2::name() const
{
    return m_name;
}

// [TODO]
/*
Variant PropertyGroup2::toVariant() const
{
}
*/

// [TODO]
/*
bool PropertyGroup2::fromVariant(const Variant & value)
{
}
*/

const std::unordered_map<std::string, AbstractProperty2 *> & PropertyGroup2::properties() const
{
    return m_propertiesMap;
}

AbstractProperty2 * PropertyGroup2::property(const std::string & path)
{
    std::vector<std::string> splittedPath = util::split(path, '/');
    return const_cast<AbstractProperty2 *>(findProperty(splittedPath));
}

const AbstractProperty2 * PropertyGroup2::property(const std::string & path) const
{
    std::vector<std::string> splittedPath = util::split(path, '/');
    return findProperty(splittedPath);
}

AbstractProperty2 * PropertyGroup2::addProperty(AbstractProperty2 * property)
{
    // Get property as abstract value
    AbstractValue * value = dynamic_cast<AbstractValue *>(property);

    // Reject properties that have no name or whose name already exists
    if (!value || !value->hasName() || this->propertyExists(value->name()))
    {
        return nullptr;
    }

    // Invoke callback
    beforeAdd(count(), property);

    // Add property
    m_properties.push_back(property);
    m_propertiesMap.insert(std::make_pair(value->name(), property));

    // Invoke callback
    afterAdd(count(), property);

    // Return property
    return property;
}

PropertyGroup2 * PropertyGroup2::group(const std::string & path)
{
    // Get property by path
    AbstractProperty2 * property = this->property(path);
    if (!property) {
        return nullptr;
    }

    // Convert into group
    return property->as<PropertyGroup2>();
}

const PropertyGroup2 * PropertyGroup2::group(const std::string & path) const
{
    // Get property by path
    const AbstractProperty2 * property = this->property(path);
    if (!property) {
        return nullptr;
    }

    // Convert into group
    return property->as<PropertyGroup2>();
}

PropertyGroup2 * PropertyGroup2::addGroup(const std::string & name)
{
    // Create group
    PropertyGroup2 * group = new PropertyGroup2(name);
    if (!this->addProperty(group))
    {
        // Abort, if group could not be added
        delete group;
        return nullptr;
    }

    return group;
}

PropertyGroup2 * PropertyGroup2::ensureGroup(const std::string & path)
{
    std::vector<std::string> splittedPath = util::split(path, '/');
    return ensureGroup(splittedPath);
}

bool PropertyGroup2::isEmpty() const
{
    return m_properties.size() == 0;
}

size_t PropertyGroup2::count() const
{
    return m_properties.size();
}

AbstractValue * PropertyGroup2::at(size_t index)
{
    // Check if index is valid
    if (index >= this->count())
    {
        return nullptr;
    }

    // Return property
    return m_properties[index]->asValue();
}

const AbstractValue * PropertyGroup2::at(size_t index) const
{
    // Check if index is valid
    if (index >= this->count())
    {
        return nullptr;
    }

    // Return property
    return m_properties[index]->asValue();
}

int PropertyGroup2::indexOf(const AbstractValue * value) const
{
    // Check input parameter
    assert(value);

    // Convert into property
    const AbstractProperty2 * property = dynamic_cast<const AbstractProperty2 *>(value);
    if (!property)
    {
        return -1;
    }

    // Check if property exists in the group
    if (!this->propertyExists(value->name()))
    {
        return -1;
    }

    // Return index of property
    return (int)std::distance(m_properties.begin(), std::find(m_properties.begin(), m_properties.end(), property));
}

void PropertyGroup2::forEach(const std::function<void(AbstractValue &)> & callback)
{
    // For each property
    for (AbstractProperty2 * property : m_properties)
    {
        // Get abstract value
        AbstractValue * value = dynamic_cast<AbstractValue *>(property);
        if (!value) {
            continue;
        }

        // Invoke callback
        callback(*value);
    }
}

void PropertyGroup2::forEach(const std::function<void(const AbstractValue &)> & callback) const
{
    // For each property
    for (AbstractProperty2 * property : m_properties)
    {
        // Get abstract value
        AbstractValue * value = dynamic_cast<AbstractValue *>(property);
        if (!value) {
            continue;
        }

        // Invoke callback
        callback(*value);
    }
}

AbstractProperty2 * PropertyGroup2::takeProperty(const std::string & name)
{
    // Check if property exists in this group
    if (!this->propertyExists(name))
    {
        return nullptr;
    }

    // Get property and property index
    AbstractProperty2 * property = m_propertiesMap.at(name);
    auto it = std::find(m_properties.begin(), m_properties.end(), property);
    size_t index = indexOf( (*it)->asValue() );

    // Invoke callback
    beforeRemove(index);

    // Remove property from group
    m_properties.erase(it);
    m_propertiesMap.erase(name);

    // Invoke callback
    afterRemove(index);

    // Return property
    return property;
}

void PropertyGroup2::clear()
{
    // Remove all properties
    auto it = m_properties.begin();
    while (it != m_properties.end())
    {
        // Get property index
        size_t index = std::distance(m_properties.begin(), it);

        // Invoke callback
        beforeRemove(index);

        // Delete property
        if (m_ownsProperties)
        {
            AbstractProperty2 * property = *it;
            delete property;
        }

        // Remove property
        m_propertiesMap.erase((*it)->asValue()->name());
        it = m_properties.erase(it);

        // Invoke callback
        afterRemove(index);
    }

    // Make sure that property list is empty
    assert(m_properties.empty());
    assert(m_propertiesMap.empty());
}

void PropertyGroup2::setOwnsProperties(bool owns)
{
    m_ownsProperties = owns;
}

bool PropertyGroup2::propertyExists(const std::string & name) const
{
    return m_propertiesMap.find(name) != m_propertiesMap.end();
}

bool PropertyGroup2::groupExists(const std::string & name) const
{
    return this->propertyExists(name) &&
           m_propertiesMap.at(name)->as<PropertyGroup2>() != nullptr;
}

void PropertyGroup2::forEach(const std::function<void(AbstractProperty2 &)> & callback)
{
    // Visit all properties
    for (AbstractProperty2 * property : m_properties)
    {
        callback(*property);
    }
}

void PropertyGroup2::forEach(const std::function<void(const AbstractProperty2 &)> & callback) const
{
    // Visit all properties
    for (const AbstractProperty2 * property : m_properties)
    {
        callback(*property);
    }
}

void PropertyGroup2::forEachCollection(const std::function<void(AbstractCollection &)> & callback)
{
    // Visit all collections
    for (AbstractProperty2 * property : m_properties)
    {
        // Check if property is a collection
        AbstractCollection * collection = dynamic_cast<AbstractCollection *>(property);
        if (collection) {
            callback(*collection);
        }
    }
}

void PropertyGroup2::forEachCollection(const std::function<void(const AbstractCollection &)> & callback) const
{
    // Visit all collections
    for (const AbstractProperty2 * property : m_properties)
    {
        // Check if property is a collection
        const AbstractCollection * collection = dynamic_cast<const AbstractCollection *>(property);
        if (collection) {
            callback(*collection);
        }
    }
}

void PropertyGroup2::forEachGroup(const std::function<void(PropertyGroup2 &)> & callback)
{
    // Visit all groups
    for (AbstractProperty2 * property : m_properties)
    {
        // Check if property is a group
        PropertyGroup2 * group = dynamic_cast<PropertyGroup2 *>(property);
        if (group) {
            callback(*group);
        }
    }
}

void PropertyGroup2::forEachGroup(const std::function<void(const PropertyGroup2 &)> & callback) const
{
    // Visit all groups
    for (const AbstractProperty2 * property : m_properties)
    {
        // Check if property is a group
        const PropertyGroup2 * group = dynamic_cast<const PropertyGroup2 *>(property);
        if (group) {
            callback(*group);
        }
    }
}

const AbstractProperty2 * PropertyGroup2::findProperty(const std::vector<std::string> & path) const
{
    // Check if path is valid
    if (path.size() == 0) {
        return nullptr;
    }

    // Check if first element of the path exists in this group
    if (!propertyExists(path.front())) {
        return nullptr;
    }

    // Get the respective property
    AbstractProperty2 * property = m_propertiesMap.at(path.front());

    // If there are no more sub-paths, return the found property
    if (path.size() == 1) {
        return property;
    }

    // Otherwise, it is an element in the middle of the path, so ensure it is a group
    if (!property->isGroup()) {
        return nullptr;
    }

    // Call recursively on subgroup
    return property->asGroup()->findProperty({ path.begin() + 1, path.end() });

    // [TODO] Use iterative approach rather than recursion
}

PropertyGroup2 * PropertyGroup2::ensureGroup(const std::vector<std::string> & path)
{
    // [TODO] Use iterative approach rather than recursion

    // Check if path is valid
    if (path.size() == 0) {
        return nullptr;
    }

    // Check if group exists
    PropertyGroup2 * group = nullptr;
    if (propertyExists(path.front()))
    {
        // Get property
        AbstractProperty2 * property = m_propertiesMap.at(path.front());

        // Abort if this is not a group
        if (!property->isGroup()) {
            return nullptr;
        }

        // Get as group
        group = property->asGroup();
    }
    else
    {
        // Add new group
        group = addGroup(path.front());
    }

    // If there are no more sub-paths, return the group
    if (path.size() == 1) {
        return group;
    }

    // Otherwise, call recursively on subgroup
    return group->ensureGroup(std::vector<std::string>(path.begin() + 1, path.end()));
}

void PropertyGroup2::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyGroup2>(this);
    visitor->callVisitor<AbstractCollection>(this);
}


} // namespace reflectionzeug
