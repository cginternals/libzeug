
#include <reflectionzeug/FilePathProperty.h>

namespace reflectionzeug
{

FilePathProperty::FilePathProperty(const FilePath & value)
:   ClassProperty<FilePath>(value)
,   m_shouldExist(true)
,   m_isFile(true)
{
}

FilePathProperty::FilePathProperty( 
    const std::function<FilePath ()> & getter,
    const std::function<void(const FilePath &)> & setter)
:   ClassProperty<FilePath>(getter, setter)
,   m_shouldExist(true)
,   m_isFile(true)
{
}

FilePathProperty::~FilePathProperty()
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
    
} // namespace reflectionzeug
