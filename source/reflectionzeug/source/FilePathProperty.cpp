
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

const std::string & FilePathProperty::uniqueIdentifier()
{
    return m_identifier;
}

void FilePathProperty::setUniqueIdentifier(const std::string & string)
{
    m_identifier = string;
}
    
} // namespace reflectionzeug
