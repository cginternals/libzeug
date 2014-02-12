
set(target propertyguizeug)
message(STATUS "Lib ${target}")

#
# External libraries
#

#
# Includes
#

include_directories(
    ${CMAKE_SOURCE_DIR}/source/signalzeug/include
    ${CMAKE_SOURCE_DIR}/source/propertyzeug/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#
# Libraries
#

set(libs
    propertyzeug
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
    ${header_path}/propertyguizeug.h
    ${header_path}/PropertyBrowser.h
    ${header_path}/PropertyModel.h
    ${header_path}/PropertyDelegate.h
    ${header_path}/PropertyPainter.h
    ${header_path}/PropertyEditorFactory.h
)

set(sources
    ${source_path}/PropertyBrowser.cpp
    ${source_path}/PropertyModel.cpp
    ${source_path}/PropertyDelegate.cpp
    ${source_path}/PropertyPainter.cpp
    ${source_path}/PropertyEditorFactory.cpp
    ${source_path}/PropertyEditor.h
    ${source_path}/PropertyEditor.cpp
    ${source_path}/BoolEditor.h
    ${source_path}/BoolEditor.cpp
    ${source_path}/IntegerEditor.h
    ${source_path}/IntegerEditor.cpp
    ${source_path}/DoubleEditor.h
    ${source_path}/DoubleEditor.cpp
    ${source_path}/StringEditor.h
    ${source_path}/StringEditor.cpp
    ${source_path}/ChoiceEditor.h
    ${source_path}/ChoiceEditor.cpp
    ${source_path}/ColorEditor.h
    ${source_path}/ColorEditor.cpp
    ${source_path}/FilePathEditor.h
    ${source_path}/FilePathEditor.cpp
    ${source_path}/MatrixEditor.h
    ${source_path}/MatrixEditor.cpp
    ${source_path}/BoolMatrixEditor.h
    ${source_path}/BoolMatrixEditor.cpp
    ${source_path}/IntMatrixEditor.h
    ${source_path}/IntMatrixEditor.cpp
    ${source_path}/IntSetEditor.h
    ${source_path}/IntSetEditor.cpp
    ${source_path}/DoubleMatrixEditor.h
    ${source_path}/DoubleMatrixEditor.cpp
    ${source_path}/SetEditor.h
    ${source_path}/SetEditor.cpp
    ${source_path}/ColorButton.h
    ${source_path}/ColorButton.cpp
    ${source_path}/TransparencyBackgroundBrush.hpp
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
qt5_use_modules(${target} Core Gui Widgets)

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
