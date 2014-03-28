
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
    FilePathProperty(const FilePath & value);
    
    FilePathProperty(const std::function<FilePath ()> & getter,
                     const std::function<void(const FilePath &)> & setter);

    template <class Object>
    FilePathProperty(Object & object, 
                     const FilePath & (Object::*getter_pointer)() const,
                     void (Object::*setter_pointer)(const FilePath &));

    template <class Object>
    FilePathProperty(Object & object, 
                     FilePath (Object::*getter_pointer)() const,
                     void (Object::*setter_pointer)(const FilePath &));
    
    template <class Object>
    FilePathProperty(Object & object, 
                     FilePath (Object::*getter_pointer)() const,
                     void (Object::*setter_pointer)(FilePath));

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
