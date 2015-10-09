
#pragma once


#include <string>

#include <iozeug/iozeug_api.h>


namespace iozeug 
{


/**
*  @brief
*    Read entire file into a string
*
*  @param[in] filePath
*    Path to file
*  @param[out] content
*    String that receives the contents of the file
*
*  @return
*    'true' if the file has been read successfully, else 'false'
*/
IOZEUG_API bool readFile(const std::string & filePath, std::string & content);

/**
*  @brief
*    Read entire file into a string
*
*  @param[in] filePath
*    Path to file
*
*  @return
*    File content as string, "" on error
*/
IOZEUG_API std::string readFile(const std::string & filePath);


} // namespace iozeug
