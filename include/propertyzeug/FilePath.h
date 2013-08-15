
#pragma once

#include <string>
#include <propertyzeug/propertyzeug.h>

namespace propertyzeug {

class PROPERTYZEUG_API FilePath
{
public:
    FilePath();
    FilePath(const FilePath & filePath);
    FilePath(const std::string & string);
    virtual ~FilePath();

    const std::string & string() const;
    void setString(const std::string & string);
    
protected:
    std::string m_string;
};

} // namespace