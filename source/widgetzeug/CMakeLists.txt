
set(target widgetzeug)
message(STATUS "Lib ${target}")

# External libraries

find_package(Qt5Core    5.1 REQUIRED)
find_package(Qt5Gui     5.1 REQUIRED)
find_package(Qt5Widgets 5.1 REQUIRED) # this is also important in order to get uic working

# Includes

include_directories(
)

include_directories(
    BEFORE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/source
    ${CMAKE_SOURCE_DIR}/source/reflectionzeug/include
)


# Libraries

set(libs
)


# Compiler definitions

if (OPTION_BUILD_STATIC)
    add_definitions("-DWIDGETZEUG_STATIC")
else()
    add_definitions("-DWIDGETZEUG_EXPORTS")
endif()


# Sources

set(header_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
    ${header_path}/widgetzeug_api.h
    ${header_path}/ColorGradient.h
    ${header_path}/ColorGradientProperty.h
    ${header_path}/ColorGradientStop.h
    ${header_path}/ColorScheme.h
    ${header_path}/ColorSchemeGraphicsItem.h
    ${header_path}/ColorSchemeGraphicsItemGroup.h
    ${header_path}/ColorSchemeGraphicsView.h
    ${header_path}/ColorSchemePresetsWidget.h
    ${header_path}/DpiAwareGraphicsView.h
    ${header_path}/RGBABrush.hpp
    ${header_path}/SingleColorSchemeGraphicsView.h
    ${header_path}/util.hpp
)

set(sources
    ${source_path}/ColorGradient.cpp
    ${source_path}/ColorGradientStop.cpp
    ${source_path}/ColorScheme.cpp
    ${source_path}/ColorSchemeGraphicsItem.cpp
    ${source_path}/ColorSchemeGraphicsItemGroup.cpp
    ${source_path}/ColorSchemeGraphicsView.cpp
    ${source_path}/ColorSchemePresetsWidget.cpp
    ${source_path}/ColorSchemePresetsWidget.ui
    ${source_path}/DpiAwareGraphicsView.cpp
    ${source_path}/SingleColorSchemeGraphicsView.cpp
)

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${header_path} "\\\\.h$|\\\\.hpp$" 
    ${header_group} ${headers})
source_group_by_path(${source_path} "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${source_group} ${sources})


# Build library

list_extract(uis "\\\\.ui$" ${sources})
qt5_wrap_ui(uihs ${uis})

if(OPTION_BUILD_STATIC)
    add_library(${target} ${headers} ${sources})
else()
    add_library(${target} SHARED ${headers} ${sources})
endif()

qt5_use_modules(${target} Core Gui Widgets)
target_link_libraries(${target} ${libs})

# qt fix - 4244 -> 'argument' : conversion from 'type1' to 'type2', possible loss of data
set(DEFAULT_COMPILE_FLAGS ${DEFAULT_COMPILE_FLAGS} " /wd4244")

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