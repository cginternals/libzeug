
set(target signalzeug)
message(STATUS "Lib ${target}")

#
# External libraries
#

#
# Includes
#

include_directories(
)

include_directories(
    BEFORE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#
# Libraries
#

set(libs
)

#
# Compiler definitions
#

if (OPTION_BUILD_STATIC)
    add_definitions("-DSIGNALZEUG_STATIC")
else()
    add_definitions("-DSIGNALZEUG_EXPORTS")
endif()

#
# Sources
#

set(header_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
    ${header_path}/signalzeug_api.h
    ${header_path}/AbstractSignal.h
    ${header_path}/Connection.h
    ${header_path}/ConnectionMap.h
    ${header_path}/ConnectionMap.hpp
    ${header_path}/ScopedConnection.h
    ${header_path}/Signal.h
    ${header_path}/Signal.hpp
)

set(sources
    ${source_path}/AbstractSignal.cpp
    ${source_path}/Connection.cpp
    ${source_path}/ConnectionMap.cpp
    ${source_path}/ScopedConnection.cpp
)

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${header_path} "\\\\.h$|\\\\.hpp$" 
    ${header_group} ${headers})
source_group_by_path(${source_path} "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${source_group} ${sources})

#
# Build library
#

if(OPTION_BUILD_STATIC)
    add_library(${target} ${headers} ${sources})
else()
    add_library(${target} SHARED ${headers} ${sources})
endif()

target_link_libraries(${target} ${libs})

set_target_properties(${target}
    PROPERTIES
    LINKER_LANGUAGE              CXX
    FOLDER                      "${IDE_FOLDER}"
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}"
    INCLUDE_PATH                "${header_path}")

#
# Deployment
#

# Library
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN}
    LIBRARY DESTINATION ${INSTALL_SHARED}
    ARCHIVE DESTINATION ${INSTALL_LIB}
)

# Header files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE})
