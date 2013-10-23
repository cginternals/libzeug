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
