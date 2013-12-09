
#pragma once

#ifdef _MSC_VER
#	define __API_EXPORT_DECLARATION __declspec(dllexport)
#	define __API_IMPORT_DECLARATION __declspec(dllimport)
#elif __GNUC__
#	define __API_EXPORT_DECLARATION
#	define __API_IMPORT_DECLARATION
#else
#	define __API_EXPORT_DECLARATION
#	define __API_IMPORT_DECLARATION
#endif

#ifdef SCRIPTZEUG_EXPORTS
#	define SCRIPTZEUG_API __API_EXPORT_DECLARATION
#else
#	define SCRIPTZEUG_API __API_IMPORT_DECLARATION
#endif
