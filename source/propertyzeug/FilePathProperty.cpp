
#include <propertyzeug/FilePathProperty.h>

namespace zeug {

FilePathProperty::FilePathProperty(const std::string & name,
    const FilePath & value)
:   ValuePropertyTemplate<FilePath>(name, value)
,   m_shouldExist(true)
,   m_isFile(true)
{
}

FilePathProperty::FilePathProperty(const std::string & name, 
    const std::function<FilePath ()> & getter,
    const std::function<void(const FilePath &)> & setter)
:   ValuePropertyTemplate<FilePath>(name, getter, setter)
,   m_shouldExist(true)
,   m_isFile(true)
{
}

template <class Object>
FilePathProperty::FilePathProperty(const std::string & name,
    Object & object, const FilePath & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const FilePath &))
:   ValuePropertyTemplate<FilePath>(name, object, getter_pointer, setter_pointer)
,   m_shouldExist(true)
,   m_isFile(true)
{
}
    
template <class Object>
FilePathProperty::FilePathProperty(const std::string & name,
    Object & object, FilePath (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(FilePath))
:   ValuePropertyTemplate<FilePath>(name, object, getter_pointer, setter_pointer)
,   m_shouldExist(true)
,   m_isFile(true)
{
}

bool FilePathProperty::shouldExist() const
{
    return m_shouldExist;
}

void FilePathProperty::setShouldExist(bool shouldExist)
{
    m_shouldExist = shouldExist;
}

bool FilePathProperty::isFile() const
{
    return m_isFile;
}

void FilePathProperty::setIsFile(bool isFile)
{
    m_isFile = isFile;
}

std::string FilePathProperty::valueAsString() const
{
    return this->value().string();
}
    
} // namespace

