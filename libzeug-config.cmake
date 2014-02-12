# LIBZEUG_FOUND
# LIBZEUG_INCLUDE_DIR

# LIBZEUG_SIGNAL_LIBRARY
# LIBZEUG_SIGNAL_LIBRARY_DEBUG
# LIBZEUG_SIGNAL_LIBRARIES

# LIBZEUG_PROPERTY_LIBRARY
# LIBZEUG_PROPERTY_LIBRARY_DEBUG
# LIBZEUG_PROPERTY_LIBRARIES

# LIBZEUG_PROPERTYGUI_LIBRARY
# LIBZEUG_PROPERTYGUI_LIBRARY_DEBUG
# LIBZEUG_PROPERTYGUI_LIBRARIES

# LIBZEUG_IO_LIBRARY
# LIBZEUG_IO_LIBRARY_DEBUG
# LIBZEUG_IO_LIBRARIES

# LIBZEUG_THREADING_LIBRARY
# LIBZEUG_THREADING_LIBRARY_DEBUG
# LIBZEUG_THREADING_LIBRARIES

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
	${LIBZEUG_DIR}/build
	${LIBZEUG_DIR}/build/Release
	${LIBZEUG_DIR}/build/Debug
	${LIBZEUG_DIR}/build-release
	${LIBZEUG_DIR}/build-debug
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

macro (find LIB_NAME HINT_PATHS)

	string(TOUPPER LIBZEUG_${LIB_NAME} LIB_NAME_UPPER)
	find_library(${LIB_NAME_UPPER}_LIBRARY
		NAMES ${LIB_NAME}zeug
		PATHS ${HINT_PATHS}
		DOC "The ${LIB_NAME} library")
	find_library(${LIB_NAME_UPPER}_LIBRARY_DEBUG
		NAMES ${LIB_NAME}zeugd
		PATHS ${HINT_PATHS}
		DOC "The ${LIB_NAME} debug library")

	if(${LIB_NAME_UPPER}_LIBRARY AND ${LIB_NAME_UPPER}_LIBRARY_DEBUG)
                set(${LIB_NAME_UPPER}_LIBRARIES "optimized" ${${LIB_NAME_UPPER}_LIBRARY} "debug" ${${LIB_NAME_UPPER}_LIBRARY_DEBUG})
        elseif(${LIB_NAME_UPPER}_LIBRARY)
                set(${LIB_NAME_UPPER}_LIBRARIES ${${LIB_NAME_UPPER}_LIBRARY})
        elseif(${LIB_NAME_UPPER}_LIBRARY_DEBUG)
                set(${LIB_NAME_UPPER}_LIBRARIES ${${LIB_NAME_UPPER}_LIBRARY_DEBUG})
        endif()
endmacro()

find(signal "${LIB_PATHS}")
find(property "${LIB_PATHS}")
find(propertygui "${LIB_PATHS}")
find(io "${LIB_PATHS}")
find(threading "${LIB_PATHS}")

find_package_handle_standard_args(LIBZEUG DEFAULT_MSG LIBZEUG_THREADING_LIBRARIES LIBZEUG_INCLUDE_DIR)
mark_as_advanced(LIBZEUG_FOUND)
