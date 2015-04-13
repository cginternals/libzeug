
# LIBZEUG_FOUND
# LIBZEUG_LIBRARIES
# LIBZEUG_INCLUDES
# LIBZEUG_BINARIES                  (win32 only)
# LIBZEUG_BINARY_[RELEASE|DEBUG]    (win32 only)

# LIBZEUG_IO_LIBRARIES
# LIBZEUG_IO_LIBRARY_[RELEASE|DEBUG]
# LIBZEUG_IO_INCLUDE_DIR
# LIBZEUG_IO_BINARIES               (win32 only)
# LIBZEUG_IO_BINARY_[RELEASE|DEBUG] (win32 only)

# LIBZEUG_LOGGING_LIBRARIES
# LIBZEUG_LOGGING_LIBRARY_[RELEASE|DEBUG]
# LIBZEUG_LOGGING_INCLUDE_DIR
# LIBZEUG_LOGGING_BINARIES               (win32 only)
# LIBZEUG_LOGGING_BINARY_[RELEASE|DEBUG] (win32 only)

# LIBZEUG_PROPERTYGUI_LIBRARIES
# LIBZEUG_PROPERTYGUI_LIBRARY_[RELEASE|DEBUG]
# LIBZEUG_PROPERTYGUI_INCLUDE_DIR
# LIBZEUG_PROPERTYGUI_BINARIES               (win32 only)
# LIBZEUG_PROPERTYGUI_BINARY_[RELEASE|DEBUG] (win32 only)

# LIBZEUG_REFLECTION_LIBRARIES
# LIBZEUG_REFLECTION_LIBRARY_[RELEASE|DEBUG]
# LIBZEUG_REFLECTION_INCLUDE_DIR
# LIBZEUG_REFLECTION_BINARIES               (win32 only)
# LIBZEUG_REFLECTION_BINARY_[RELEASE|DEBUG] (win32 only)

# LIBZEUG_SCRIPT_LIBRARIES
# LIBZEUG_SCRIPT_LIBRARY_[RELEASE|DEBUG]
# LIBZEUG_SCRIPT_INCLUDE_DIR
# LIBZEUG_SCRIPT_BINARIES               (win32 only)
# LIBZEUG_SCRIPT_BINARY_[RELEASE|DEBUG] (win32 only)

# LIBZEUG_SIGNAL_LIBRARIES
# LIBZEUG_SIGNAL_LIBRARY_[RELEASE|DEBUG]
# LIBZEUG_SIGNAL_INCLUDE_DIR
# LIBZEUG_SIGNAL_BINARIES               (win32 only)
# LIBZEUG_SIGNAL_BINARY_[RELEASE|DEBUG] (win32 only)

# LIBZEUG_THREADING_LIBRARIES
# LIBZEUG_THREADING_LIBRARY_[RELEASE|DEBUG]
# LIBZEUG_THREADING_INCLUDE_DIR
# LIBZEUG_THREADING_BINARIES               (win32 only)
# LIBZEUG_THREADING_BINARY_[RELEASE|DEBUG] (win32 only)

# LIBZEUG_WIDGET_LIBRARIES
# LIBZEUG_WIDGET_LIBRARY_[RELEASE|DEBUG]
# LIBZEUG_WIDGET_INCLUDE_DIR
# LIBZEUG_WIDGET_BINARIES               (win32 only)
# LIBZEUG_WIDGET_BINARY_[RELEASE|DEBUG] (win32 only)

macro (find LIB_NAME HEADER)
    set(HINT_PATHS ${ARGN})

    string(TOUPPER LIBZEUG_${LIB_NAME} LIB_NAME_UPPER)
    set(LIBNAME ${LIB_NAME}zeug)

    find_path(${LIB_NAME_UPPER}_INCLUDE_DIR ${HEADER}
        ${ENVLIBZEUG_DIR}/include
        ${ENVLIBZEUG_DIR}/source/${LIBNAME}/include
        ${LIBZEUG_DIR}/include
        ${LIBZEUG_DIR}/source/${LIBNAME}/include
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
        set(${LIB_NAME_UPPER}_LIBRARIES "optimized" ${${LIB_NAME_UPPER}_LIBRARY_RELEASE} "debug" ${${LIB_NAME_UPPER}_LIBRARY_DEBUG})
    elseif(${LIB_NAME_UPPER}_LIBRARY_RELEASE)
        set(${LIB_NAME_UPPER}_LIBRARIES ${${LIB_NAME_UPPER}_LIBRARY_RELEASE})
    elseif(${LIB_NAME_UPPER}_LIBRARY_DEBUG)
        set(${LIB_NAME_UPPER}_LIBRARIES ${${LIB_NAME_UPPER}_LIBRARY_DEBUG})
    endif()

    # find binaries
    if (WIN32 AND ${LIB_NAME_UPPER}_LIBRARIES)
        set(${LIB_NAME_UPPER}_BINARIES "")

        find_file(${LIB_NAME_UPPER}_BINARY_RELEASE
            NAMES ${LIBNAME}.dll
            PATHS
            ${LIBZEUG_DIR}/bin
            ${LIBZEUG_DIR}/build/Release
            ${LIBZEUG_DIR}/build-release
            DOC "The ${LIB_NAME_UPPER} binary")

        find_file(${LIB_NAME_UPPER}_BINARY_DEBUG
            NAMES ${LIBNAME}d.dll
            PATHS
            ${LIBZEUG_DIR}/bin
            ${LIBZEUG_DIR}/build/Debug
            ${LIBZEUG_DIR}/build-debug
            DOC "The ${LIB_NAME_UPPER} debug binary")

        if(NOT ${LIB_NAME_UPPER}_BINARY_RELEASE STREQUAL "${LIB_NAME_UPPER}_BINARY_RELEASE-NOTFOUND")
            list(APPEND ${LIB_NAME_UPPER}_BINARIES ${${LIB_NAME_UPPER}_BINARY_RELEASE})
        endif()

        if(NOT ${LIB_NAME_UPPER}_BINARY_DEBUG STREQUAL "${LIB_NAME_UPPER}_BINARY_DEBUG-NOTFOUND")
            list(APPEND ${LIB_NAME_UPPER}_BINARIES ${${LIB_NAME_UPPER}_BINARY_DEBUG})
        endif()
    endif()

    list(APPEND LIBZEUG_INCLUDES ${${LIB_NAME_UPPER}_INCLUDE_DIR})
    list(APPEND LIBZEUG_LIBRARIES ${${LIB_NAME_UPPER}_LIBRARIES})
    list(APPEND LIBZEUG_BINARIES ${${LIB_NAME_UPPER}_BINARIES})

    # DEBUG
    #message("${LIB_NAME_UPPER}_INCLUDE_DIR     = ${${LIB_NAME_UPPER}_INCLUDE_DIR}")
    #message("${LIB_NAME_UPPER}_LIBRARY_RELEASE = ${${LIB_NAME_UPPER}_LIBRARY_RELEASE}")
    #message("${LIB_NAME_UPPER}_LIBRARY_DEBUG   = ${${LIB_NAME_UPPER}_LIBRARY_DEBUG}")
    #message("${LIB_NAME_UPPER}_LIBRARY         = ${${LIB_NAME_UPPER}_LIBRARY}")

endmacro()


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

find(io          iozeug/iozeug_api.h                   ${LIB_PATHS})
find(logging     loggingzeug/loggingzeug_api.h         ${LIB_PATHS})
find(propertygui propertyguizeug/propertyguizeug_api.h ${LIB_PATHS})
find(reflection  reflectionzeug/reflectionzeug_api.h   ${LIB_PATHS})
find(script      scriptzeug/scriptzeug_api.h           ${LIB_PATHS})
find(signal      signalzeug/signalzeug_api.h           ${LIB_PATHS})
find(threading   threadingzeug/threadingzeug_api.h     ${LIB_PATHS})
find(widget      widgetzeug/widgetzeug_api.h           ${LIB_PATHS})

# DEBUG
#message("LIBZEUG_INCLUDES  = ${LIBZEUG_INCLUDES}")
#message("LIBZEUG_LIBRARIES = ${LIBZEUG_LIBRARIES}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBZEUG DEFAULT_MSG LIBZEUG_LIBRARIES LIBZEUG_INCLUDES)
mark_as_advanced(LIBZEUG_FOUND)
