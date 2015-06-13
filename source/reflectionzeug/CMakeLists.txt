
set(target reflectionzeug)
message(STATUS "Lib ${target}")


# External libraries

# Fallback: Use boost regex
if(NOT OPTION_BUILD_WITH_STD_REGEX)
    find_package(Boost COMPONENTS regex REQUIRED)
endif()


# Includes

if(NOT OPTION_BUILD_WITH_STD_REGEX)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(
    BEFORE
    ${CMAKE_SOURCE_DIR}/source/signalzeug/include
    ${CMAKE_SOURCE_DIR}/source/loggingzeug/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# Libraries

set(libs
    signalzeug
    loggingzeug
)

if(NOT OPTION_BUILD_WITH_STD_REGEX)
    link_directories(${Boost_LIBRARY_DIR})
    set(libs ${libs} ${Boost_LIBRARIES})
endif()


# Compiler definitions

if (OPTION_BUILD_STATIC)
    add_definitions("-DREFLECTIONZEUG_STATIC")
else()
    add_definitions("-DREFLECTIONZEUG_EXPORTS")
endif()

if(OPTION_BUILD_WITH_STD_REGEX)
    add_definitions("-DUSE_STD_REGEX")
endif()


# Sources

set(header_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
    ${header_path}/reflectionzeug_api.h

    ${header_path}/base/util.h
    ${header_path}/base/util.hpp
    ${header_path}/base/Color.h
    ${header_path}/base/FilePath.h

    ${header_path}/specialization_helpers.h
    ${header_path}/AbstractValue.h
    ${header_path}/AbstractCollection.h
    ${header_path}/AbstractTyped.h
    ${header_path}/AbstractTyped.hpp
    ${header_path}/AbstractTypedArray.h
    ${header_path}/AbstractTypedArray.hpp
    ${header_path}/Accessor.h
    ${header_path}/Accessor.hpp
    ${header_path}/AccessorGetSet.h
    ${header_path}/AccessorGetSet.hpp
    ${header_path}/AccessorValue.h
    ${header_path}/AccessorValue.hpp
    ${header_path}/ArrayAccessor.h
    ${header_path}/ArrayAccessor.hpp
    ${header_path}/ArrayAccessorGetSet.h
    ${header_path}/ArrayAccessorGetSet.hpp
    ${header_path}/ArrayAccessorValue.h
    ${header_path}/ArrayAccessorValue.hpp
    ${header_path}/Typed.h
    ${header_path}/Typed.hpp
    ${header_path}/TypedEnum.h
    ${header_path}/TypedEnum.hpp
    ${header_path}/TypedArray.h
    ${header_path}/TypedArray.hpp
    ${header_path}/TypedBool.h
    ${header_path}/TypedBool.hpp
    ${header_path}/TypedClass.h
    ${header_path}/TypedClass.hpp
    ${header_path}/TypedColor.h
    ${header_path}/TypedColor.hpp
    ${header_path}/TypedFilePath.h
    ${header_path}/TypedFilePath.hpp
    ${header_path}/TypedFloatingPoint.h
    ${header_path}/TypedFloatingPoint.hpp
    ${header_path}/TypedSignedIntegral.h
    ${header_path}/TypedSignedIntegral.hpp
    ${header_path}/TypedString.h
    ${header_path}/TypedString.hpp
    ${header_path}/TypedUnsignedIntegral.h
    ${header_path}/TypedUnsignedIntegral.hpp
    ${header_path}/NamedTyped.h
    ${header_path}/NamedTyped.hpp
    ${header_path}/AbstractBooleanInterface.h
    ${header_path}/AbstractStringInterface.h
    ${header_path}/AbstractColorInterface.h
    ${header_path}/AbstractFloatingPointInterface.h
    ${header_path}/AbstractSignedIntegralInterface.h
    ${header_path}/AbstractUnsignedIntegralInterface.h
    ${header_path}/AbstractEnumInterface.h
    ${header_path}/AbstractProperty.h
    ${header_path}/AbstractProperty.hpp
    ${header_path}/AbstractVisitor.h
    ${header_path}/AbstractVisitor.hpp
    ${header_path}/PropertyGroup.h
    ${header_path}/PropertyGroup.hpp
    ${header_path}/Property.h
    ${header_path}/Property.hpp
    ${header_path}/Visitor.h
    ${header_path}/Variant.h
    ${header_path}/Variant.hpp
)

set(sources
    ${source_path}/base/util.cpp
    ${source_path}/base/Color.cpp
    ${source_path}/base/FilePath.cpp

    ${source_path}/AbstractValue.cpp
    ${source_path}/AbstractCollection.cpp
    ${source_path}/AbstractBooleanInterface.cpp
    ${source_path}/AbstractStringInterface.cpp
    ${source_path}/AbstractColorInterface.cpp
    ${source_path}/AbstractFloatingPointInterface.cpp
    ${source_path}/AbstractSignedIntegralInterface.cpp
    ${source_path}/AbstractUnsignedIntegralInterface.cpp
    ${source_path}/AbstractEnumInterface.cpp
    ${source_path}/AbstractProperty.cpp
    ${source_path}/AbstractVisitor.cpp
    ${source_path}/PropertyGroup.cpp
    ${source_path}/Variant.cpp
)

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${header_path} "\\\\.h$|\\\\.hpp$"
    ${header_group} ${headers})
source_group_by_path(${source_path} "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$"
    ${source_group} ${sources})


# Build library

if(OPTION_BUILD_STATIC)
    add_library(${target} ${headers} ${sources})
else()
    add_library(${target} SHARED ${headers} ${sources})
endif()

target_link_libraries(${target} ${libs})

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
