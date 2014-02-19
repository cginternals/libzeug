
#pragma once

#include <reflectionzeug/ValuePropertyTemplate.h>
#include <reflectionzeug/FilePath.h>

#include <reflectionzeug/reflectionzeug.h>

namespace reflectionzeug
{
    
/** \brief Part of the property hierarchy that  manages a file path.
 */
class REFLECTIONZEUG_API FilePathProperty : public ValuePropertyTemplate<FilePath>
{
public:
    FilePathProperty(const std::string & name, const FilePath & value);
    
    FilePathProperty(const std::string & name,
                     const std::function<FilePath ()> & getter,
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

} // namespace reflectionzeug
