
#include <reflectionzeug/FilePathProperty.h>

namespace reflectionzeug
{

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
