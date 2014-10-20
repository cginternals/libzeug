
set(target propertyguizeug)
message(STATUS "Lib ${target}")

#
# External libraries
#

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

#
# Includes
#

include_directories(
)

include_directories(
    BEFORE
    ${CMAKE_SOURCE_DIR}/source/signalzeug/include
    ${CMAKE_SOURCE_DIR}/source/reflectionzeug/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#
# Libraries
#

set(libs
    reflectionzeug
	signalzeug
    # this target link libraries somehow fixes the include directories for used qt modules.
    # (not nice! since it obfuscates the common cmake way to link 3rdp libraries..., 
    #  but seems to be intended by qt: http://qt-project.org/doc/qt-5/cmake-manual.html)
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

#
# Compiler definitions
#

if (OPTION_BUILD_STATIC)
    add_definitions("-DPROPERTYGUIZEUG_STATIC")
else()
    add_definitions("-DPROPERTYGUIZEUG_EXPORTS")
endif()

#
# Sources
#

set(header_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
    ${header_path}/propertyguizeug_api.h
    ${header_path}/AbstractPropertyEditorPlugin.h
    ${header_path}/BoolEditor.h
    ${header_path}/ColorButton.h
    ${header_path}/ColorEditor.h
    ${header_path}/EnumEditor.h
    ${header_path}/FilePathEditor.h
    ${header_path}/FloatingPointEditor.h
    ${header_path}/LongLongSpinBox.h
    ${header_path}/PropertyBrowser.h
    ${header_path}/PropertyDelegate.h
    ${header_path}/PropertyEditor.h
    ${header_path}/PropertyEditorFactory.h
    ${header_path}/PropertyModel.h
    ${header_path}/PropertyPainter.h
    ${header_path}/SignedIntegralEditor.h
    ${header_path}/StringEditor.h
    ${header_path}/ULongLongSpinBox.h
    ${header_path}/UnsignedIntegralEditor.h
    ${header_path}/ValueEditor.h
)

set(sources
    ${source_path}/AbstractPropertyEditorPlugin.cpp
    ${source_path}/BoolEditor.cpp
    ${source_path}/ColorButton.cpp
    ${source_path}/ColorEditor.cpp
    ${source_path}/EnumEditor.cpp
    ${source_path}/FilePathEditor.cpp
    ${source_path}/FloatingPointEditor.cpp
    ${source_path}/LongLongSpinBox.cpp
    ${source_path}/PropertyBrowser.cpp
    ${source_path}/PropertyDelegate.cpp
    ${source_path}/PropertyEditor.cpp
    ${source_path}/PropertyEditorFactory.cpp
    ${source_path}/PropertyItem.cpp
    ${source_path}/PropertyItem.h
    ${source_path}/PropertyModel.cpp
    ${source_path}/PropertyPainter.cpp
    ${source_path}/SignedIntegralEditor.cpp
    ${source_path}/StringEditor.cpp
    ${source_path}/TransparencyBackgroundBrush.hpp
    ${source_path}/ULongLongSpinBox.cpp
    ${source_path}/UnsignedIntegralEditor.cpp
    ${source_path}/ValueEditor.cpp
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
