# Target
set(target propertyguizeug)
message(STATUS "lib ${target}")

# Qt 5 Dependencies
set(CMAKE_AUTOMOC ON)

# Include directories
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}/../../  # for Meta.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

# Libraries
set(libs
    propertyzeug
)

# Definitions
add_definitions("-DPROPERTYGUIZEUG_EXPORTS")

# Sources
set(header_path "${LIBZEUG_SOURCE_DIR}/include/propertyguizeug")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}")

set(headers
    ${header_path}/propertyguizeug.h

    ${header_path}/WidgetBuilder.h
    ${header_path}/PropertyItemModel.h
)

set(sources
    ${source_path}/WidgetBuilder.cpp
    ${source_path}/PropertyItemModel.cpp
)

# Group source files
set(propertyguizeug_header_group "Header Files (API)")
set(propertyguizeug_source_group "Source Files")
source_group_by_path(${header_path} "\\\\.h$|\\\\.hpp$" 
    ${propertyguizeug_header_group} ${headers})
source_group_by_path(${source_path} "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${propertyguizeug_source_group} ${sources})

# Build library
if(OPTION_BUILD_STATIC)
    add_library(${target} ${headers} ${sources})
else()
    add_library(${target} SHARED ${headers} ${sources})
endif()
target_link_libraries(${target} ${libs})
qt5_use_modules(${target} Core Gui Widgets)
set_target_properties(${target}
    PROPERTIES
    LINKER_LANGUAGE CXX
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}"
    INCLUDE_PATH                "${CMAKE_CURRENT_SOURCE_DIR}/../../include")

# Deployment
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN}
    LIBRARY DESTINATION ${INSTALL_SHARED}
    ARCHIVE DESTINATION ${INSTALL_LIB}
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../include/ DESTINATION ${INSTALL_INCLUDE})
