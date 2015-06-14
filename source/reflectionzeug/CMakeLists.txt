
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

    ${header_path}/type/specialization_helpers.h
    ${header_path}/type/AbstractValue.h
    ${header_path}/type/AbstractCollection.h
    ${header_path}/type/AbstractTyped.h
    ${header_path}/type/AbstractTyped.hpp
    ${header_path}/type/AbstractTypedArray.h
    ${header_path}/type/AbstractTypedArray.hpp
    ${header_path}/type/AbstractAccessor.h
    ${header_path}/type/Accessor.h
    ${header_path}/type/Accessor.hpp
    ${header_path}/type/AccessorGetSet.h
    ${header_path}/type/AccessorGetSet.hpp
    ${header_path}/type/AccessorValue.h
    ${header_path}/type/AccessorValue.hpp
    ${header_path}/type/ArrayAccessor.h
    ${header_path}/type/ArrayAccessor.hpp
    ${header_path}/type/ArrayAccessorGetSet.h
    ${header_path}/type/ArrayAccessorGetSet.hpp
    ${header_path}/type/ArrayAccessorValue.h
    ${header_path}/type/ArrayAccessorValue.hpp
    ${header_path}/type/Typed.h
    ${header_path}/type/Typed.hpp
    ${header_path}/type/TypedEnum.h
    ${header_path}/type/TypedEnum.hpp
    ${header_path}/type/TypedArray.h
    ${header_path}/type/TypedArray.hpp
    ${header_path}/type/TypedBool.h
    ${header_path}/type/TypedBool.hpp
    ${header_path}/type/TypedClass.h
    ${header_path}/type/TypedClass.hpp
    ${header_path}/type/TypedColor.h
    ${header_path}/type/TypedColor.hpp
    ${header_path}/type/TypedFilePath.h
    ${header_path}/type/TypedFilePath.hpp
    ${header_path}/type/TypedFloatingPoint.h
    ${header_path}/type/TypedFloatingPoint.hpp
    ${header_path}/type/TypedSignedIntegral.h
    ${header_path}/type/TypedSignedIntegral.hpp
    ${header_path}/type/TypedString.h
    ${header_path}/type/TypedString.hpp
    ${header_path}/type/TypedUnsignedIntegral.h
    ${header_path}/type/TypedUnsignedIntegral.hpp
    ${header_path}/type/NamedTyped.h
    ${header_path}/type/NamedTyped.hpp
    ${header_path}/type/AbstractBooleanInterface.h
    ${header_path}/type/AbstractStringInterface.h
    ${header_path}/type/AbstractColorInterface.h
    ${header_path}/type/AbstractFloatingPointInterface.h
    ${header_path}/type/AbstractSignedIntegralInterface.h
    ${header_path}/type/AbstractUnsignedIntegralInterface.h
    ${header_path}/type/AbstractEnumInterface.h
    ${header_path}/type/AbstractVisitor.h
    ${header_path}/type/AbstractVisitor.hpp
    ${header_path}/type/Visitor.h

    ${header_path}/tools/JSON.h
    ${header_path}/tools/JSONReader.h

    ${header_path}/AbstractProperty.h
    ${header_path}/AbstractProperty.hpp
    ${header_path}/PropertyGroup.h
    ${header_path}/PropertyGroup.hpp
    ${header_path}/Property.h
    ${header_path}/Property.hpp
    ${header_path}/Variant.h
    ${header_path}/Variant.hpp
)

set(sources
    ${source_path}/base/util.cpp
    ${source_path}/base/Color.cpp
    ${source_path}/base/FilePath.cpp

    ${source_path}/type/AbstractAccessor.cpp
    ${source_path}/type/AbstractValue.cpp
    ${source_path}/type/AbstractCollection.cpp
    ${source_path}/type/AbstractBooleanInterface.cpp
    ${source_path}/type/AbstractStringInterface.cpp
    ${source_path}/type/AbstractColorInterface.cpp
    ${source_path}/type/AbstractFloatingPointInterface.cpp
    ${source_path}/type/AbstractSignedIntegralInterface.cpp
    ${source_path}/type/AbstractUnsignedIntegralInterface.cpp
    ${source_path}/type/AbstractEnumInterface.cpp
    ${source_path}/type/AbstractVisitor.cpp
    ${source_path}/type/TypedBool.cpp
    ${source_path}/type/TypedString.cpp
    ${source_path}/type/TypedColor.cpp
    ${source_path}/type/TypedFilePath.cpp

    ${source_path}/tools/JSON.cpp
    ${source_path}/tools/JSONReader.cpp

    ${source_path}/AbstractProperty.cpp
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
