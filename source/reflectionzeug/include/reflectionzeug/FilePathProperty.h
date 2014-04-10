
#pragma once

#include <reflectionzeug/ClassProperty.h>
#include <reflectionzeug/FilePath.h>

#include <reflectionzeug/reflectionzeug.h>

namespace reflectionzeug
{
    
/** \brief Part of the property hierarchy that  manages a file path.
 */
class REFLECTIONZEUG_API FilePathProperty : public ClassProperty<FilePath>
{
public:
    template <typename... Arguments>
    FilePathProperty(Arguments&&... args);

    virtual ~FilePathProperty() = 0;
    
    bool shouldExist() const;
    void setShouldExist(bool shouldExist);

    bool isFile() const;
    void setIsFile(bool isFile);
  
protected:
    bool m_shouldExist;
    bool m_isFile;
    
};

} // namespace reflectionzeug

#include "FilePathProperty.hpp"
