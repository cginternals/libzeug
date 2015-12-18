
# 
# External dependencies
# 

find_package(Qt5Core    5.1 REQUIRED)
find_package(Qt5Gui     5.1 REQUIRED)
find_package(Qt5Widgets 5.1 REQUIRED)

# Enable automoc
set(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
set(AUTOMOC_MOC_OPTIONS PROPERTIES FOLDER CMakeAutomocTargets)
set_property(GLOBAL PROPERTY AUTOMOC_FOLDER CMakeAutomocTargets)

# ENABLE CMP0020: Automatically link Qt executables to qtmain target on Windows.
if (POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()


# 
# Library name and options
# 

# Target name
set(target widgetzeug)

# Exit here if required dependencies are not met
message(STATUS "Lib ${target}")

# Set API export file and macro
string(TOUPPER ${target} target_upper)
set(export_file  "include/${target}/${target}_api.h")
set(export_macro "${target_upper}_API")


# 
# Sources
# 

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path  "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
    ${include_path}/make_unique.hpp
    ${include_path}/RGBABrush.hpp
    ${include_path}/dark_fusion_style.hpp

    ${include_path}/ControlWidgetSettings.h
    # color widgets
    ${include_path}/ColorGradient.h
    #${include_path}/ColorGradientProperty.h
    ${include_path}/ColorGradientStop.h
    #${include_path}/ColorGradientWidget.h
    ${include_path}/ColorScheme.h
    ${include_path}/ColorSchemeControlWidget.h
    ${include_path}/ColorSchemeLabel.h
    ${include_path}/ColorSchemePresets.h
    ${include_path}/ColorSchemePresetsWidget.h
    ${include_path}/ColorSchemeWidget.h
    ${include_path}/ColorVisionDeficiency.h
    # multi-purpose widgets
    ${include_path}/DataLinkWidget.h
    ${include_path}/DockableScrollAreaWidget.h
    ${include_path}/DpiAware.h
    ${include_path}/DpiAwareGraphicsView.h
    ${include_path}/DpiAwareWidget.h
    # script widgets
    ${include_path}/ECMA26251_Completer.h
    ${include_path}/ECMA26251_SyntaxHighlighter.h
    ${include_path}/ScriptCompleter.h
    ${include_path}/ScriptPromptWidget.h
    ${include_path}/ScriptSyntaxHighlighter.h
    # log widgets
    ${include_path}/AbstractMessageReceiver.h
    ${include_path}/MessageHandler.h
    ${include_path}/MessageStatusWidget.h
    ${include_path}/MessageWidget.h
)

set(sources
    ${source_path}/util.hpp

    ${source_path}/ControlWidgetSettings.cpp
    # color widgets
    ${source_path}/ColorGradient.cpp
    #${source_path}/ColorGradientLabel.cpp
    #${source_path}/ColorGradientLabel.h
    #${source_path}/ColorGradientMidpointBar.cpp
    #${source_path}/ColorGradientMidpointBar.h
    #${source_path}/ColorGradientMidpointWidget.cpp
    #${source_path}/ColorGradientMidpointWidget.h
    #${source_path}/ColorGradientModel.cpp
    #${source_path}/ColorGradientModel.h
    ${source_path}/ColorGradientStop.cpp
    #${source_path}/ColorGradientStopBar.cpp
    #${source_path}/ColorGradientStopBar.h
    #${source_path}/ColorGradientStopModel.cpp
    #${source_path}/ColorGradientStopModel.h
    #${source_path}/ColorGradientStopWidget.cpp
    #${source_path}/ColorGradientStopWidget.h
    #${source_path}/ColorGradientWidget.cpp
    #${source_path}/ColorGradientWidget.ui
    ${source_path}/ColorScheme.cpp
    ${source_path}/ColorSchemeControlWidget.cpp
    ${source_path}/ColorSchemeGraphicsItem.cpp
    ${source_path}/ColorSchemeGraphicsItem.h  
    ${source_path}/ColorSchemeGraphicsItemGroup.cpp
    ${source_path}/ColorSchemeGraphicsItemGroup.h
    ${source_path}/ColorSchemeGraphicsView.cpp
    ${source_path}/ColorSchemeGraphicsView.h
    ${source_path}/ColorSchemeLabel.cpp
    ${source_path}/ColorSchemePresets.cpp
    ${source_path}/ColorSchemePresetsWidget.cpp
    ${source_path}/ColorSchemePresetsWidget.ui
    ${source_path}/ColorSchemeWidget.cpp
    ${source_path}/ColorSchemeWidget.ui
    ${source_path}/ColorVisionDeficiency.cpp
    # multi-purpose widgets
    ${source_path}/DataLinkWidget.cpp
    ${source_path}/DataLinkWidget.ui
    ${source_path}/DockableScrollAreaWidget.cpp
    ${source_path}/DpiAware.cpp
    ${source_path}/DpiAwareGraphicsView.cpp
    ${source_path}/DpiAwareWidget.cpp
    # script widgets
    ${source_path}/ECMA26251_Completer.cpp
    ${source_path}/ECMA26251_SyntaxHighlighter.cpp
    ${source_path}/ScriptCompleter.cpp
    ${source_path}/ScriptPromptWidget.cpp
    ${source_path}/ScriptSyntaxHighlighter.cpp
    # log widgets
    ${source_path}/MessageHandler.cpp
    ${source_path}/MessageStatusWidget.cpp
    ${source_path}/MessageWidget.cpp
)

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${include_path} "\\\\.h$|\\\\.hpp$" 
    ${header_group} ${headers})
source_group_by_path(${source_path}  "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${source_group} ${sources})


# 
# Create library
# 

# Build library
add_library(${target}
    ${sources}
    ${headers}
)

# Create namespaced alias
add_library(${META_PROJECT_NAME}::${target} ALIAS ${target})

# Export library for downstream projects
export(TARGETS ${target} NAMESPACE ${META_PROJECT_NAME}:: FILE ${PROJECT_BINARY_DIR}/cmake/${target}/${target}-export.cmake)

# Create API export header
generate_export_header(${target}
    EXPORT_FILE_NAME  ${export_file}
    EXPORT_MACRO_NAME ${export_macro}
)


# 
# Project options
# 

set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
    FOLDER "${IDE_FOLDER}"
)

# 
# Include directories
# 

target_include_directories(${target}
    PRIVATE    # Includes that are needed internally for this project
    ${PROJECT_BINARY_DIR}/source/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/source
    ${CMAKE_CURRENT_BINARY_DIR}

    PUBLIC     # Includes that are needed for this project AND for any downstream project using this library
    ${DEFAULT_INCLUDE_DIRECTORIES}

    INTERFACE  # Includes for downstream projects to use this project
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)


# 
# Libraries
# 

target_link_libraries(${target}
    PRIVATE    # Libraries that are needed internally for this project
    
    PUBLIC     # Libraries that are needed for this project AND for any downstream project using this library
    ${DEFAULT_LIBRARIES}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets

    INTERFACE  # Libraries for downstream projects to use this library
)


# 
# Compile definitions
# 

target_compile_definitions(${target}
    PRIVATE    # Definitions that are needed internally for this project

    PUBLIC     # Definitions that are needed for this project AND for any downstream project using this library
    $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:${target_upper}_STATIC_DEFINE>
    ${DEFAULT_COMPILE_DEFINITIONS}

    INTERFACE  # Definitions for downstream projects to use this library
)


# 
# Compile options
# 

target_compile_options(${target}
    PRIVATE    # Options that are needed internally for this project

    PUBLIC     # Options that are needed for this project AND for any downstream project using this library
    ${DEFAULT_COMPILE_OPTIONS}

    INTERFACE  # Options for downstream projects to use this library
)


# 
# Linker options
# 

target_link_libraries(${target}
    PRIVATE    # Options that are needed internally for this project

    PUBLIC     # Options that are needed for this project AND for any downstream project using this library
    ${DEFAULT_LINKER_OPTIONS}

    INTERFACE  # Options for downstream projects to use this library
)


# 
# Deployment
# 

# Library
install(TARGETS ${target}
    EXPORT  "${target}-export"            COMPONENT dev
    RUNTIME DESTINATION ${INSTALL_BIN}    COMPONENT runtime
    LIBRARY DESTINATION ${INSTALL_SHARED} COMPONENT runtime
    ARCHIVE DESTINATION ${INSTALL_LIB}    COMPONENT dev
)

# Header files
install(DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE}
    COMPONENT dev
)

# Generated header files
install(DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE}
    COMPONENT dev
)

# CMake config
install(EXPORT ${target}-export
    NAMESPACE   ${META_PROJECT_NAME}::
    DESTINATION ${INSTALL_CMAKE}/${target}
    COMPONENT   dev
)
