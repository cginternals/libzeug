
# LIBZEUG_FOUND

# LIBZEUG_LIBRARIES
# LIBZEUG_INCLUDES

# LIBZEUG_SIGNAL_LIBRARY
# LIBZEUG_SIGNAL_LIBRARY_RELEASE
# LIBZEUG_SIGNAL_LIBRARY_DEBUG
# LIBZEUG_SIGNAL_INCLUDE_DIR

# LIBZEUG_REFLECTION_LIBRARY
# LIBZEUG_REFLECTION_LIBRARY_RELEASE
# LIBZEUG_REFLECTION_LIBRARY_DEBUG
# LIBZEUG_REFLECTION_INCLUDE_DIR

# LIBZEUG_PROPERTYGUI_LIBRARY
# LIBZEUG_PROPERTYGUI_LIBRARY_RELEASE
# LIBZEUG_PROPERTYGUI_LIBRARY_DEBUG
# LIBZEUG_PROPERTYGUI_INCLUDE_DIR

# LIBZEUG_IO_LIBRARY
# LIBZEUG_IO_LIBRARY_RELEASE
# LIBZEUG_IO_LIBRARY_DEBUG
# LIBZEUG_IO_INCLUDE_DIR

# LIBZEUG_THREADING_LIBRARY
# LIBZEUG_THREADING_LIBRARY_RELEASE
# LIBZEUG_THREADING_LIBRARY_DEBUG
# LIBZEUG_THREADING_INCLUDE_DIR

# LIBZEUG_SCRIPT_LIBRARY
# LIBZEUG_SCRIPT_LIBRARY_RELEASE
# LIBZEUG_SCRIPT_LIBRARY_DEBUG
# LIBZEUG_SCRIPT_INCLUDE_DIR



include(FindPackageHandleStandardArgs)

if(CMAKE_CURRENT_LIST_FILE)
    get_filename_component(LIBZEUG_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)
endif()

file(TO_CMAKE_PATH "$ENV{PROGRAMFILES}" ENVPROGRAMFILES)
file(TO_CMAKE_PATH "$ENV{LIBZEUG_DIR}"  ENVLIBZEUG_DIR)

set(LIB_PATHS   
    ${LIBZEUG_DIR}/build
    ${LIBZEUG_DIR}/build/Release
    ${LIBZEUG_DIR}/build/Debug
    ${LIBZEUG_DIR}/build-release
    ${LIBZEUG_DIR}/build-debug
    ${ENVLIBZEUG_DIR}/lib
    ${LIBZEUG_DIR}/lib
    ${ENVPROGRAMFILES}/libzeug/lib
    /usr/lib
    /usr/local/lib
    /sw/lib
    /opt/local/lib
    /usr/lib64
    /usr/local/lib64
    /sw/lib64
    /opt/local/lib64
)

macro (find LIB_NAME HEADER)
    set(HINT_PATHS ${ARGN})

    string(TOUPPER LIBZEUG_${LIB_NAME} LIB_NAME_UPPER)
    set(LIBNAME ${LIB_NAME}zeug)

    find_path(${LIB_NAME_UPPER}_INCLUDE_DIR ${HEADER}
        ${ENVLIBZEUG_DIR}/include
        ${ENVLIBZEUG_DIR}/source/${LIB_NAME}/include
        ${LIBZEUG_DIR}/include
        ${LIBZEUG_DIR}/source/${LIB_NAME}/include
        ${ENVPROGRAMFILES}/libzeug/include
        /usr/include
        /usr/local/include
        /sw/include
        /opt/local/include
        DOC "The directory where ${HEADER} resides")

    find_library(${LIB_NAME_UPPER}_LIBRARY_RELEASE
        NAMES ${LIBNAME}
        PATHS ${HINT_PATHS}
        DOC "The ${LIB_NAME} library")
    find_library(${LIB_NAME_UPPER}_LIBRARY_DEBUG
        NAMES ${LIBNAME}d
        PATHS ${HINT_PATHS}
        DOC "The ${LIB_NAME} debug library")
    
    if(${LIB_NAME_UPPER}_LIBRARY_RELEASE AND ${LIB_NAME_UPPER}_LIBRARY_DEBUG)
        set(${LIB_NAME_UPPER}_LIBRARY "optimized" ${${LIB_NAME_UPPER}_LIBRARY_RELEASE} "debug" ${${LIB_NAME_UPPER}_LIBRARY_DEBUG})
    elseif(${LIB_NAME_UPPER}_LIBRARY_RELEASE)
        set(${LIB_NAME_UPPER}_LIBRARY ${${LIB_NAME_UPPER}_LIBRARY_RELEASE})
    elseif(${LIB_NAME_UPPER}_LIBRARY_DEBUG)
        set(${LIB_NAME_UPPER}_LIBRARY ${${LIB_NAME_UPPER}_LIBRARY_DEBUG})
    endif()

    set(LIBZEUG_INCLUDES  ${LIBZEUG_INCLUDES}  ${${LIB_NAME_UPPER}_INCLUDE_DIR})
    set(LIBZEUG_LIBRARIES ${LIBZEUG_LIBRARIES} ${${LIB_NAME_UPPER}_LIBRARY})

    # DEBUG
    #message("${LIB_NAME_UPPER}_INCLUDE_DIR     = ${${LIB_NAME_UPPER}_INCLUDE_DIR}")
    #message("${LIB_NAME_UPPER}_LIBRARY_RELEASE = ${${LIB_NAME_UPPER}_LIBRARY_RELEASE}")
    #message("${LIB_NAME_UPPER}_LIBRARY_DEBUG   = ${${LIB_NAME_UPPER}_LIBRARY_DEBUG}")
    #message("${LIB_NAME_UPPER}_LIBRARY         = ${${LIB_NAME_UPPER}_LIBRARY}")

endmacro()

find(signal      signalzeug/signalzeug.h ${LIB_PATHS})
find(reflection  reflectionzeug/reflectionzeug.h ${LIB_PATHS})
find(propertygui propertyguizeug/propertyguizeug.h ${LIB_PATHS})
find(io          iozeug/iozeug.h ${LIB_PATHS})
find(threading   threadingzeug/threadingzeug.h ${LIB_PATHS})
find(script      scriptzeug/scriptzeug.h ${LIB_PATHS})

# DEBUG
#message("LIBZEUG_INCLUDES  = ${LIBZEUG_INCLUDES}")
#message("LIBZEUG_LIBRARIES = ${LIBZEUG_LIBRARIES}")

find_package_handle_standard_args(LIBZEUG DEFAULT_MSG LIBZEUG_LIBRARIES LIBZEUG_INCLUDES)
mark_as_advanced(LIBZEUG_FOUND)
