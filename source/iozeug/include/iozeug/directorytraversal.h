
#pragma once


#include <string>

#include <iozeug/iozeug_api.h>


namespace iozeug
{


/**
*  @brief
*    List all files in a directory
*
*  @param[in] dirName
*    Path to directory (exluding a trailing '/'!)
*  @param[in] recursive
*    Search recursively in sub-directories?
*  @param[out] files
*    List of files
*
*  @remarks
*    Lists all files in the directory, including all
*    files in sub-directories if recursive is true.
*    Only files are listed, directories are not included.
*    The search path is included in the file name, e.g.,
*    getFile("dir") may result in ["dir/file1.txt", "dir/file2.png", ...].
*/
IOZEUG_API void getFiles(const std::string & directory, bool recursive, std::vector<std::string> & files);

/**
*  @brief
*    List all files in a directory
*
*  @param[in] dirName
*    Path to directory (exluding a trailing '/'!)
*  @param[in] recursive
*    Search recursively in sub-directories?
*
*  @return
*    List of files
*/
IOZEUG_API std::vector<std::string> getFiles(const std::string & directory, bool recursive);

/**
*  @brief
*    Scan directory for files with a specific filename extension
*
*  @param[in] directory
*    Path to directory
*  @param[in] fileExtension
*    File extension ("*" for all files)
*  @param[in] recursive
*    Search recursively in sub-directories?
*
*  @return
*    List of found files, including the directory name
*/
IOZEUG_API std::vector<std::string> scanDirectory(const std::string & directory, const std::string & fileExtension, bool recursive = false);

/**
*  @brief
*    Scan directory for files with a specific filename extension
*
*  @param[in] directory
*    Path to directory
*  @param[in] fileExtension
*    File extension ("*" for all files)
*  @param[in] recursive
*    Search recursively in sub-directories?
*  @param[in] callback
*    Function that is called for each found file
*
*  @return
*    List of found files, including the directory name
*/
IOZEUG_API std::vector<std::string> scanDirectory(const std::string & directory, const std::string & fileExtension, bool recursive = false);


} // namespace iozeug
