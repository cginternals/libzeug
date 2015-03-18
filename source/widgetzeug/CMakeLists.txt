
set(target widgetzeug)
message(STATUS "Lib ${target}")

# External libraries

find_package(Qt5Core    5.1 REQUIRED)
find_package(Qt5Gui     5.1 REQUIRED)
find_package(Qt5OpenGL  5.1 REQUIRED)
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
    ${CMAKE_SOURCE_DIR}/source/signalzeug/include
)


# Libraries

set(libs
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
#    Qt5::OpenGL
#    reflectionzeug
#    signalzeug
)


# Compiler definitions

if (OPTION_BUILD_STATIC)
    add_definitions("-DLIBZEUGZEUG_STATIC")
else()
    add_definitions("-DWIDGETZEUG_EXPORTS")
endif()


# Sources

set(header_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(api_includes
    ${header_path}/widgetzeug_api.h   
    ${header_path}/RGBABrush.hpp
    ${header_path}/dark_fusion_style.hpp

    ${header_path}/ControlWidgetSettings.h
    # color widgets
    #${header_path}/ColorGradient.h
    #${header_path}/ColorGradientProperty.h
    #${header_path}/ColorGradientStop.h
    #${header_path}/ColorGradientWidget.h
    ${header_path}/ColorScheme.h
    ${header_path}/ColorSchemeControlWidget.h
	${header_path}/ColorSchemeLabel.h
    ${header_path}/ColorSchemePresets.h
    ${header_path}/ColorSchemePresetsWidget.h
    ${header_path}/ColorSchemeWidget.h
    ${header_path}/ColorVisionDeficiency.h
    # multi-purpose widgets
    ${header_path}/DataLinkWidget.h
    ${header_path}/DockableScrollAreaWidget.h
    ${header_path}/DpiAware.h
    ${header_path}/DpiAwareGraphicsView.h
    ${header_path}/DpiAwareWidget.h
    # script widgets
    ${header_path}/ECMA26251_Completer.h
    ${header_path}/ECMA26251_SyntaxHighlighter.h
    ${header_path}/ScriptCompleter.h
    ${header_path}/ScriptPromptWidget.h
    ${header_path}/ScriptSyntaxHighlighter.h
    # log widgets
    ${header_path}/AbstractMessageReceiver.h
    ${header_path}/MessageHandler.h
    ${header_path}/MessageStatusWidget.h
    ${header_path}/MessageWidget.h
)

set(sources
    ${source_path}/util.hpp

    ${source_path}/ControlWidgetSettings.cpp
    # color widgets
    #${source_path}/ColorGradient.cpp
    #${source_path}/ColorGradientLabel.cpp
    #${source_path}/ColorGradientLabel.h
    #${source_path}/ColorGradientMidpointBar.cpp
    #${source_path}/ColorGradientMidpointBar.h
    #${source_path}/ColorGradientMidpointWidget.cpp
    #${source_path}/ColorGradientMidpointWidget.h
    #${source_path}/ColorGradientModel.cpp
    #${source_path}/ColorGradientModel.h
    #${source_path}/ColorGradientStop.cpp
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
source_group_by_path(${header_path} "\\\\.h$|\\\\.hpp$" 
    ${header_group} ${api_includes})
source_group_by_path(${source_path} "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${source_group} ${sources})


# Build library

list_extract(uis "\\\\.ui$" ${sources})
qt5_wrap_ui(uihs ${uis})

add_library(${target} ${api_includes} ${sources})

target_link_libraries(${target} ${libs})

if(MSVC)
    # 'argument' : conversion from 'type1' to 'type2', possible loss of data (problem in qt)
    set(DEFAULT_COMPILE_FLAGS ${DEFAULT_COMPILE_FLAGS} /wd4244)
    # -> msvc14 : declaration hides class member (problem in qt)
    set(DEFAULT_COMPILE_FLAGS ${DEFAULT_COMPILE_FLAGS} /wd4458)
endif()

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
