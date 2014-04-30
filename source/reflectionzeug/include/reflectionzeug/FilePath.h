
#pragma once

#include <string>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{

/** 
 * \brief A simple file path class for use as a property value.
 */
class REFLECTIONZEUG_API FilePath
{
public:
    static FilePath fromString(const std::string & string, bool * ok);

public:
    FilePath();
    FilePath(const FilePath & filePath);
    FilePath(const std::string & string);
    FilePath(const char * string);
    virtual ~FilePath();

    const std::string & string() const;
    void setString(const std::string & string);

    const std::string & toString() const;

protected:
    std::string m_string;
};

} // namespace reflectionzeug
