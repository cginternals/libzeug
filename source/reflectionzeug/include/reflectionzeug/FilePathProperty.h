
#pragma once

#include <string>

#include <reflectionzeug/ClassProperty.h>
#include <reflectionzeug/FilePath.h>

#include <reflectionzeug/reflectionzeug_api.h>

namespace reflectionzeug
{
    
/**
 * \brief Extends the ClassProperty by some file path specific flags.
 */
class FilePathProperty : public ClassProperty<FilePath>
{
public:
    template <typename... Arguments>
    FilePathProperty(Arguments&&... args);

    REFLECTIONZEUG_API virtual ~FilePathProperty() = 0;
    
    REFLECTIONZEUG_API bool shouldExist() const;
    REFLECTIONZEUG_API void setShouldExist(bool shouldExist);

    REFLECTIONZEUG_API bool isFile() const;
    REFLECTIONZEUG_API void setIsFile(bool isFile);
    
    REFLECTIONZEUG_API const std::string & uniqueIdentifier();
    REFLECTIONZEUG_API void setUniqueIdentifier(const std::string & string);
  
protected:
    bool m_shouldExist;
    bool m_isFile;
    std::string m_identifier;
    
};

} // namespace reflectionzeug

#include "FilePathProperty.hpp"
