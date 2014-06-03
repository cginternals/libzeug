
set(target scriptzeug)
message(STATUS "Lib ${target}")

#
# External libraries
#

find_package(V8)
option(LIBZEUG_USE_V8 "Use V8 for JavaScript backend" ${V8_FOUND})

#
# Includes
#

if (LIBZEUG_USE_V8 AND V8_FOUND)
    include_directories(
        ${V8_INCLUDE_DIR}
    )
endif()

include_directories(
    BEFORE
    ${CMAKE_SOURCE_DIR}/source/signalzeug/include
    ${CMAKE_SOURCE_DIR}/source/reflectionzeug/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/source
)

#
# Libraries
#

set(libs
    reflectionzeug
    signalzeug
)

if (LIBZEUG_USE_V8 AND V8_FOUND)
    set(libs ${libs}
        ${V8_LIBRARY}
    )
endif()

#
# Compiler definitions
#

if (OPTION_BUILD_STATIC)
    add_definitions("-DSCRIPTZEUG_STATIC")
else()
    add_definitions("-DSCRIPTZEUG_EXPORTS")
endif()

if (LIBZEUG_USE_V8 AND V8_FOUND)
    add_definitions("-DLIBZEUG_USE_V8")
endif()

#
# Sources
#

set(header_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
    ${header_path}/ScriptContext.h
    ${header_path}/Backend/AbstractScriptContext.h
)

set(sources
    ${source_path}/ScriptContext.cpp
    ${source_path}/Backend/AbstractScriptContext.cpp
)

if (LIBZEUG_USE_V8 AND V8_FOUND)
    set(sources ${sources}
        ${source_path}/BackendJavaScript/JSScriptContext.cpp
    )
    set(headers ${headers}
        ${source_path}/BackendJavaScript/JSScriptContext.h
    )
endif()

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

generate_library_export_header(${target})

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
install(FILES ${PROJECT_BINARY_DIR}/source/${target}/${target}_api.h DESTINATION ${INSTALL_INCLUDE}/${target})
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE})
