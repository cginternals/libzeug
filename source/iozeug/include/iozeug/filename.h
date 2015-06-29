
#pragma once


#include <string>

#include <iozeug/iozeug_api.h>


namespace iozeug
{


/**
*  @brief
*    Get filename extension
*
*  @param[in] filename
*    File name including extension (e.g., 'myfile.txt')
*  @return
*    File extension without dot (e.g., 'txt')
*
*  @remarks
*    This function searches for the last occurence of '.' and returns
*    the remaining string, so 'myarchive.tar.gz' will return 'gz'
*    rather than 'tar.gz'. If the filename is empty or has no extension,
*    an empty string is returned.
*/
IOZEUG_API std::string getExtension(const std::string & filename);


} // namespace iozeug
