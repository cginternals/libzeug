
#pragma once


#include <string>

#include <iozeug/iozeug_api.h>


namespace iozeug
{


/**
*  @brief
*    A file path class that stores the path as string and provides common
*    operations like getting the file name or extension.
*    All operations are completely string-based and don't use any system information.
*/
class IOZEUG_API FilePath
{
public:
    static FilePath fromString(const std::string & string);


public:
    FilePath();
    FilePath(const FilePath & filePath);
    FilePath(const std::string & string);
    FilePath(const char * string);
    virtual ~FilePath();

    /**
    *  @brief
    *    Get the path.
    *
    *  @return
    *    The path as string as it is stored in the FilePath class.
    */
    const std::string & path() const;

    /**
    *  @brief
    *    Get the path as uniform string, with only forward slashes '/'.
    *
    *  @return
    *    The path as uniform string (with only forward slashes '/').
    */
    std::string uniformPath() const;

    /**
    *  @brief
    *    Set the path.
    */
    void setPath(const std::string & path);

    /**
    *  @brief
    *    Get the base name.
    *
    *  @return
    *    The base name of the file the stored path points to, without extension.
    *    If the path is a directory (only recognizable by a trailing slash), an empty string is returned.
    */
    std::string baseName() const;

    /**
    *  @brief
    *    Get the full file name.
    *
    *  @return
    *    The name of the file the stored path points to, with extension.
    *    If the path is a directory (only recognizable by a trailing slash), an empty string is returned.
    */
    std::string fileName() const;

    /**
    *  @brief
    *    Get the extension.
    *
    *  @return
    *    The extension of the file the stored path points to.
    *    If the path has no extension, an empty string is returned.
    */
    std::string extension() const;

    /**
    *  @brief
    *    Get the directory path.
    *
    *  @return
    *    The path to the directory, with trailing slashes.
    *
    *  @remarks
    *    The returned path string is in unified form, so only forward slashes '/' are used.
    */
    std::string directoryPath() const;

    /**
    *  @brief
    *    Get the drive letter.
    *
    *  @return
    *    The drive letter of the path on Windows (e.g., "C").
    *    If there is no drive letter (Linux, Max), an empty string is returned.
    */
    std::string driveLetter() const;


protected:
    std::string m_string;
};


} // namespace reflectionzeug
