# Find externals
find_package(V8)
option(LIBZEUG_USE_V8 "Use V8 for JavaScript backend" ${V8_FOUND})

# Target
set(target scriptzeug)
message(STATUS "lib ${target}")

# Include directories
set(includes
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Libraries
set(libs
    propertyzeug
    signalzeug
)

# Definitions
add_definitions("-DSCRIPTZEUG_EXPORTS")

# Sources
set(header_path "${LIBZEUG_SOURCE_DIR}/include/scriptzeug")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}")

set(headers
    ${header_path}/scriptzeug.h
    ${header_path}/Backend/AbstractScriptContext.h
    ${header_path}/ScriptContext.h
    ${header_path}/Object.h
    ${header_path}/Function.h
    ${header_path}/Variant.h
    ${header_path}/TemplateHelper.h
)

set(sources
    ${source_path}/Backend/AbstractScriptContext.cpp
    ${source_path}/ScriptContext.cpp
    ${source_path}/Object.cpp
    ${source_path}/Variant.cpp
)

# Backend: JavaScript (V8 engine)
if (LIBZEUG_USE_V8)
    add_definitions("-DLIBZEUG_USE_V8")
    set(includes ${includes}
        ${V8_INCLUDE_DIR}
    )
    set(libs ${libs}
        ${V8_LIBRARY}
    )
    set(sources ${sources}
        ${source_path}/BackendJavaScript/JSScriptContext.cpp
        ${source_path}/BackendJavaScript/JSPropVisitor.cpp
    )
    set(headers ${headers}
        ${header_path}/BackendJavaScript/JSScriptContext.h
    )
endif()

# Group source files
set(propertyzeug_header_group "Header Files (API)")
set(propertyzeug_source_group "Source Files")
source_group_by_path(${header_path} "\\\\.h$|\\\\.hpp$" 
    ${propertyzeug_header_group} ${headers})
source_group_by_path(${source_path} "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${propertyzeug_source_group} ${sources})

# Build library

include_directories(${includes})

if(OPTION_BUILD_STATIC)
    add_library(${target} ${headers} ${sources})
else()
    add_library(${target} SHARED ${headers} ${sources})
endif()

target_link_libraries(${target} ${libs})

set_target_properties(${target}
    PROPERTIES
    LINKER_LANGUAGE CXX
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}"
    INCLUDE_PATH                "${LIBZEUG_SOURCE_DIR}/include")

# Deployment
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN}
    LIBRARY DESTINATION ${INSTALL_SHARED}
    ARCHIVE DESTINATION ${INSTALL_LIB}
)
