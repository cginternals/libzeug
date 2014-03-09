
#pragma once

namespace reflectionzeug
{

template <class Object>
FilePathProperty::FilePathProperty(const std::string & name,
    Object & object, const FilePath & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const FilePath &))
:   ValueProperty(name)
,   ClassProperty<FilePath>(name, object, getter_pointer, setter_pointer)
,   m_shouldExist(true)
,   m_isFile(true)
{
}

template <class Object>
FilePathProperty::FilePathProperty(const std::string & name,
    Object & object, FilePath (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const FilePath &))
:   ValueProperty(name)
,   ClassProperty<FilePath>(name, object, getter_pointer, setter_pointer)
,   m_shouldExist(true)
,   m_isFile(true)
{
}
    
template <class Object>
FilePathProperty::FilePathProperty(const std::string & name,
    Object & object, FilePath (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(FilePath))
:   ValueProperty(name)
,   ClassProperty<FilePath>(name, object, getter_pointer, setter_pointer)
,   m_shouldExist(true)
,   m_isFile(true)
{
}

} // namespace reflectionzeug
