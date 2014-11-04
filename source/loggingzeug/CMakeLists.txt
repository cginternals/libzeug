
set(target loggingzeug)
message(STATUS "Lib ${target}")


# External libraries


# Includes

include_directories(
    BEFORE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# Libraries

set(libs
)


# Compiler definitions

if (OPTION_BUILD_STATIC)
    add_definitions("-DLOGGINGZEUG_STATIC")
else()
    add_definitions("-DLOGGINGZEUG_EXPORTS")
endif()


# Sources

set(header_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
    ${header_path}/loggingzeug_api.h

    ${header_path}/AbstractLogHandler.h
    ${header_path}/ConsoleLogHandler.h
    ${header_path}/FileLogHandler.h
    ${header_path}/LogMessage.h
    ${header_path}/LogMessageBuilder.h
    ${header_path}/LogMessageBuilder.hpp
    ${header_path}/formatString.h
    ${header_path}/formatString.hpp
    ${header_path}/logging.h
    ${header_path}/logging.hpp
)

set(sources
    ${source_path}/ConsoleLogHandler.cpp
    ${source_path}/FileLogHandler.cpp
    ${source_path}/LogMessage.cpp
    ${source_path}/LogMessageBuilder.cpp
    ${source_path}/formatString.cpp
    ${source_path}/logging.cpp
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


# Deployment

# Library
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN}
    LIBRARY DESTINATION ${INSTALL_SHARED}
    ARCHIVE DESTINATION ${INSTALL_LIB}
)

# Header files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE})
