
#pragma once

#include <propertyzeug/ValueProperty.h>
#include <propertyzeug/FilePath.h>

#include <propertyzeug/propertyzeug.h>

namespace zeug 
{
    
/** @brief
 * Part of the property hierarchy.
 * Manages a FilePath.
 */

class PROPERTYZEUG_API FilePathProperty : public ValueProperty<FilePath>
{
public:
    FilePathProperty(const std::string & name, const FilePath & value);
    
    FilePathProperty(const std::string & name,
                   const std::function<const FilePath & ()> & getter,
                   const std::function<void(const FilePath &)> & setter);
    
    template <class Object>
    FilePathProperty(const std::string & name,
                   Object & object, const FilePath & (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(const FilePath &));
    
    template <class Object>
    FilePathProperty(const std::string & name,
                   Object & object, FilePath (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(FilePath));
    
    bool shouldExist() const;
    void setShouldExist(bool shouldExist);

    bool isFile() const;
    void setIsFile(bool isFile);

    virtual std::string valueAsString() const;
  
protected:
    bool m_shouldExist;
    bool m_isFile;
};

} // namespace zeug
