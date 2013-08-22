# Target
set(target propertyzeug)
message(STATUS "lib ${target}")

# Qt 5 Dependencies
set(CMAKE_AUTOMOC ON)

# Include directories
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}/../../  # for Meta.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

# Libraries
set(libs
)

# Definitions
add_definitions("-DPROPERTYZEUG_EXPORTS")

# Sources
set(header_path "${LIBZEUG_SOURCE_DIR}/include/propertyzeug")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}")

set(headers
    ${header_path}/propertyzeug.h
    # ${header_path}/Property.h
    # ${header_path}/DynObject.h

    ${header_path}/Events.h
    ${header_path}/Announcer.h

    ${header_path}/AbstractProperty.h
    ${header_path}/BaseProperty.h
    ${header_path}/LimitProperty.h
    ${header_path}/StringProperty.h
    ${header_path}/Property.h

    ${header_path}/PropertyGroup.h
    ${header_path}/AbstractPropertyVisitor.h
    ${header_path}/PropertyDeserializer.h

    ${header_path}/AbstractValue.h
    ${header_path}/StoredValue.h
    ${header_path}/AccessorValue.h

    ${header_path}/Color.h
    ${header_path}/FilePath.h
)

set(sources
    # ${source_path}/DynObject.cpp

    ${source_path}/AbstractProperty.cpp
    ${source_path}/Announcer.cpp
    ${source_path}/StringProperty.cpp

    ${source_path}/PropertyGroup.cpp
    ${source_path}/AbstractPropertyVisitor.cpp
    ${source_path}/PropertyDeserializer.cpp
    
    ${source_path}/Color.cpp
    ${source_path}/FilePath.cpp
)

# Group source files
set(propertyzeug_header_group "Header Files (API)")
set(propertyzeug_source_group "Source Files")
source_group_by_path(${header_path} "\\\\.h$|\\\\.hpp$" 
    ${propertyzeug_header_group} ${headers})
source_group_by_path(${source_path} "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${propertyzeug_source_group} ${sources})

# Build library
if(OPTION_BUILD_STATIC)
    add_library(${target} ${headers} ${sources})
else()
    add_library(${target} SHARED ${headers} ${sources})
endif()
target_link_libraries(${target} ${libs})
qt5_use_modules(${target} Core)
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
