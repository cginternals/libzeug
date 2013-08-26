
#pragma once

#include <string>
#include <propertyzeug/propertyzeug.h>

namespace propertyzeug {
    
/** @brief
 * A simple file path class for use as a property value.
 */

class PROPERTYZEUG_API FilePath
{
public:
    FilePath();
    FilePath(const FilePath & filePath);
    FilePath(const std::string & string);
    FilePath(const char * string);
    virtual ~FilePath();

    const std::string & string() const;
    void setString(const std::string & string);
    
protected:
    std::string m_string;
};

} // namespace