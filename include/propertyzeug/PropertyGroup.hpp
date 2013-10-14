
#pragma once

namespace zeug {

template <typename Type>
Property<Type> * PropertyGroup::addProperty(const std::string & name, const Type & value)
{
    auto property = new Property<Type>(name, value);
    
    if (this->addProperty(property))
        return property;
    
    delete property;
    return nullptr;
}

template <typename Type>
Property<Type> * PropertyGroup::addProperty(const std::string & name,
    const std::function<Type ()> & getter,
    const std::function<void(const Type &)> & setter)
{
    auto property = new Property<Type>(name, getter, setter);

    if (this->addProperty(property))
        return property;
    
    delete property;
    return nullptr;
}

//template <typename Type, class Object>
//Property<Type> * PropertyGroup::addProperty(const std::string & name,
//    Object & object, const Type & (Object::*getter_pointer)() const,
//    void (Object::*setter_pointer)(const Type &))
//{
//    auto property = new Property<Type>(name, object, getter_pointer, setter_pointer);
//
//    if (this->addProperty(property))
//        return property;
//    
//    delete property;
//    return nullptr;
//}

template <typename Type, class Object>
Property<Type> * PropertyGroup::addProperty(const std::string & name,
    Object & object, Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
{
    auto property = new Property<Type>(name, object, getter_pointer, setter_pointer);

    if (this->addProperty(property))
        return property;
    
    delete property;
    return nullptr;
}

template <typename Type>
Property<Type> * PropertyGroup::property(const std::string & name)
{
    return this->property(name)->as<Property<Type>>();
}
    
template <typename Type>
const Property<Type> * PropertyGroup::property(const std::string & name) const
{
    return this->property(name)->as<Property<Type>>();
}

template <typename Type>
Type PropertyGroup::value(const std::string & name) const
{
    /** TODO handle non-existence of property **/
    return this->property(name)->as<Property<Type>>()->value();
}

template <typename Type>
void PropertyGroup::setValue(const std::string & name, const Type & value)
{
    /** TODO handle non-existence of property **/
    this->property(name)->as<Property<Type>>()->setValue(value);
}

} // namespace zeug