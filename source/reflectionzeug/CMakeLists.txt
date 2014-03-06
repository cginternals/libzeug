
set(target reflectionzeug)
message(STATUS "Lib ${target}")

#
# External libraries
#

# Fallback: Use boost regex
if(NOT OPTION_BUILD_WITH_STD_REGEX)
    find_package(Boost COMPONENTS regex REQUIRED)
endif()

#
# Includes
#

if(NOT OPTION_BUILD_WITH_STD_REGEX)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(
    BEFORE
    ${CMAKE_SOURCE_DIR}/source/signalzeug/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#
# Libraries
#

set(libs
    signalzeug
)

if(NOT OPTION_BUILD_WITH_STD_REGEX)
    link_directories(${Boost_LIBRARY_DIR})
    set(libs ${libs}
        ${Boost_LIBRARIES}
    )
endif()

#
# Compiler definitions
#

if (OPTION_BUILD_STATIC)
    add_definitions("-DREFLECTIONZEUG_STATIC")
else()
    add_definitions("-DREFLECTIONZEUG_EXPORTS")
endif()

if(OPTION_BUILD_WITH_STD_REGEX)
    add_definitions("-DUSE_STD_REGEX")
endif()

#
# Sources
#

set(header_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
    ${header_path}/reflectionzeug.h

    ${header_path}/AbstractProperty.h
    ${header_path}/AbstractProperty.hpp
    ${header_path}/ValueProperty.h
    ${header_path}/ValuePropertyTemplate.h
    ${header_path}/ValuePropertyTemplate.hpp
    ${header_path}/NumberProperty.h
    ${header_path}/NumberProperty.hpp
    ${header_path}/StringProperty.h
    ${header_path}/StringProperty.hpp
    ${header_path}/VectorProperty.h
    ${header_path}/VectorProperty.hpp
    ${header_path}/FilePathProperty.h
    ${header_path}/Property.h

    ${header_path}/PropertyGroup.h
    ${header_path}/PropertyGroup.hpp
    ${header_path}/AbstractPropertyVisitor.h
    ${header_path}/PropertyVisitor.h
    ${header_path}/StandardPropertyVisitor.h
    ${header_path}/PropertyDeserializer.h
    ${header_path}/PropertyDeserializer.hpp
    ${header_path}/PropertySerializer.h

    ${header_path}/AbstractValue.h
    ${header_path}/StoredValue.h
    ${header_path}/StoredValue.hpp
    ${header_path}/AccessorValue.h
    ${header_path}/AccessorValue.hpp

    ${header_path}/Color.h
    ${header_path}/FilePath.h

    ${header_path}/Object.h
    ${header_path}/Function.h
    ${header_path}/Variant.h
    ${header_path}/TemplateHelper.h

    ${header_path}/Utility.h
    ${header_path}/Utility.hpp
)

set(sources
    ${source_path}/AbstractProperty.cpp
    ${source_path}/ValueProperty.cpp
    ${source_path}/StringProperty.cpp
    ${source_path}/FilePathProperty.cpp

    ${source_path}/PropertyGroup.cpp
    ${source_path}/PropertyDeserializer.cpp
    ${source_path}/PropertySerializer.cpp

    ${source_path}/Color.cpp
    ${source_path}/FilePath.cpp

    ${source_path}/Object.cpp
    ${source_path}/Variant.cpp
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
