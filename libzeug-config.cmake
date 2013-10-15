
# LIBZEUG_FOUND
# LIBZEUG_INCLUDE_DIR
# LIBZEUG_SIGNAL_LIBRARY
# LIBZEUG_STAGE_LIBRARY
# LIBZEUG_TREE_LIBRARY
# LIBZEUG_TREEIMPORT_LIBRARY
# LIBZEUG_PROPERTY_LIBRARY
# LIBZEUG_PROPERTYGUI_LIBRARY

find_path(LIBZEUG_INCLUDE_DIR signalzeug/Signal.h
	$ENV{LIBZEUG_DIR}/include
	${LIBZEUG_DIR}/include
	$ENV{PROGRAMFILES}/LIBZEUG/include
	/usr/include
	/usr/local/include
	/sw/include
	/opt/local/include
	DOC "The directory where signalzeug/Signal.h resides")
	
set(LIB_PATHS 	
	$ENV{LIBZEUG_DIR}/lib
	${LIBZEUG_DIR}/lib
	/usr/lib
	/usr/local/lib
	/sw/lib
	/opt/local/lib
	/usr/lib64
	/usr/local/lib64
	/sw/lib64
	/opt/local/lib64
)

find_library(LIBZEUG_SIGNAL_LIBRARY
	NAMES signalzeug
	PATHS ${LIB_PATHS}
	DOC "The signalzeug library")

find_library(LIBZEUG_STAGE_LIBRARY
	NAMES stagezeug
	PATHS ${LIB_PATHS}
	DOC "The stagezeug library")

find_library(LIBZEUG_TREE_LIBRARY
	NAMES treezeug
	PATHS ${LIB_PATHS}
	DOC "The treezeug library")
	
find_library(LIBZEUG_TREEIMPORT_LIBRARY
	NAMES treeimportzeug
	PATHS ${LIB_PATHS}
	DOC "The treeimportzeug library")
	
find_library(LIBZEUG_PROPERTY_LIBRARY
	NAMES propertyzeug
	PATHS ${LIB_PATHS}
	DOC "The propertyzeug library")
	
find_library(LIBZEUG_PROPERTYGUI_LIBRARY
	NAMES propertyguizeug
	PATHS ${LIB_PATHS}
	DOC "The propertyguizeug library")

IF(LIBZEUG_INCLUDE_DIR AND LIBZEUG_SIGNAL_LIBRARY)
    SET(LIBZEUG_FOUND 1 CACHE STRING "Set to 1 if LIBZEUG is found, 0 otherwise")
ELSE()
    SET(LIBZEUG_FOUND 0 CACHE STRING "Set to 1 if LIBZEUG is found, 0 otherwise")
    MESSAGE(WARNING "Note: an envvar like LIBZEUG_DIR assists this script to locate LIBZEUG.")
ENDIF()

MARK_AS_ADVANCED(LIBZEUG_FOUND)
