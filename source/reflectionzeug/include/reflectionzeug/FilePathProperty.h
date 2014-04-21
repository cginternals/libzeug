
#pragma once

#include <reflectionzeug/ClassProperty.h>
#include <reflectionzeug/FilePath.h>

#include <reflectionzeug/reflectionzeug_api.h>

namespace reflectionzeug
{
    
/** \brief Part of the property hierarchy that  manages a file path.
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
  
protected:
    bool m_shouldExist;
    bool m_isFile;
    
};

} // namespace reflectionzeug

#include "FilePathProperty.hpp"
