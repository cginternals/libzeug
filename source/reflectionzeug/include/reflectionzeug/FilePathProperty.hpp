
#pragma once

namespace reflectionzeug
{

template <class Object>
FilePathProperty::FilePathProperty(
    Object & object, 
    const FilePath & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const FilePath &))
:   ClassProperty<FilePath>(object, getter_pointer, setter_pointer)
,   m_shouldExist(true)
,   m_isFile(true)
{
}

template <class Object>
FilePathProperty::FilePathProperty(
    Object & object, 
    FilePath (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const FilePath &))
:   ClassProperty<FilePath>(object, getter_pointer, setter_pointer)
,   m_shouldExist(true)
,   m_isFile(true)
{
}
    
template <class Object>
FilePathProperty::FilePathProperty(
    Object & object, 
    FilePath (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(FilePath))
:   ClassProperty<FilePath>(object, getter_pointer, setter_pointer)
,   m_shouldExist(true)
,   m_isFile(true)
{
}

} // namespace reflectionzeug
