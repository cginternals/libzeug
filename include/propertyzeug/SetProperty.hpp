
#pragma once

namespace zeug {
    
template <typename Set>
SetProperty<Set>::SetProperty(const std::string & name,
    const Set & value)
:   ValuePropertyTemplate<Set>(name, value)
{
}

template <typename Set>
SetProperty<Set>::SetProperty(const std::string & name,
    const std::function<Set ()> & getter,
    const std::function<void(const Set &)> & setter)
:   ValuePropertyTemplate<Set>(name, getter, setter)
{
}

template <typename Set>
template <class Object>
SetProperty<Set>::SetProperty(const std::string & name,
    Object & object, const Set & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Set &))
:   ValuePropertyTemplate<Set>(name, object, getter_pointer, setter_pointer)
{
}

template <typename Set>
template <class Object>
SetProperty<Set>::SetProperty(const std::string & name,
    Object & object, Set (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Set &))
:   ValuePropertyTemplate<Set>(name, object, getter_pointer, setter_pointer)
{
}

template <typename Set>
SetProperty<Set>::~SetProperty()
{
}

template <typename Set>
Set SetProperty<Set>::value() const
{
    return ValuePropertyTemplate<Set>::value();
}

template <typename Set>
void SetProperty<Set>::setValue(const Set & value)
{
    ValuePropertyTemplate<Set>::setValue(value);
}

template <typename Set>
std::string SetProperty<Set>::valueAsString() const
{
    return "(" + join(this->value(), ", ") + ")";
}

template <typename Set>
std::string SetProperty<Set>::join(const Set & set,
    const std::string & separator)
{
    std::stringstream stream;
    for (Set::iterator it = set.begin(); it != set.end(); ++it)
    {
	stream << set.at(i);
	
	if (it+1 != set.end())
	    stream << separator;
    }
    
    return stream.str();
}

} // namespace
