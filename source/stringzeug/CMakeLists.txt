
set(target stringzeug)
message(STATUS "Lib ${target}")


# External libraries

# Fallback: Use boost regex
if(NOT OPTION_BUILD_WITH_STD_REGEX)
    find_package(Boost COMPONENTS regex REQUIRED)
endif()


# Includes

if(NOT OPTION_BUILD_WITH_STD_REGEX)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(
    BEFORE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/source
)


# Libraries

set(libs
)

if(NOT OPTION_BUILD_WITH_STD_REGEX)
    link_directories(${Boost_LIBRARY_DIR})
    set(libs ${libs} ${Boost_LIBRARIES})
endif()


# Compiler definitions

if (OPTION_BUILD_STATIC)
    add_definitions("-DSTRINGZEUG_STATIC")
else()
    add_definitions("-DSTRINGZEUG_EXPORTS")
endif()

if(OPTION_BUILD_WITH_STD_REGEX)
    add_definitions("-DUSE_STD_REGEX")
endif()


# Sources

set(header_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
    ${header_path}/stringzeug_api.h
    ${header_path}/conversion.h
    ${header_path}/conversion.hpp
    ${header_path}/regex.h
    ${header_path}/manipulation.h
    ${header_path}/manipulation.hpp
)

set(sources
    ${source_path}/conversion.cpp
    ${source_path}/regex.cpp
    ${source_path}/manipulation.cpp
)

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${header_path} "\\\\.h$|\\\\.hpp$" 
    ${header_group} ${headers})
source_group_by_path(${source_path} "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${source_group} ${sources})


# Build library

if(OPTION_BUILD_STATIC)
    add_library(${target} ${headers} ${sources})
else()
    add_library(${target} SHARED ${headers} ${sources})
endif()

target_link_libraries(${target} ${libs})

target_compile_options(${target} PRIVATE ${DEFAULT_COMPILE_FLAGS})

set_target_properties(${target}
    PROPERTIES
    LINKER_LANGUAGE              CXX
    FOLDER                      "${IDE_FOLDER}"
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}"
    INCLUDE_PATH                "${header_path}")


# Deployment

# Library
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN}
    LIBRARY DESTINATION ${INSTALL_SHARED}
    ARCHIVE DESTINATION ${INSTALL_LIB}
)

# Header files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE})