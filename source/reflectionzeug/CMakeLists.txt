
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
    ${header_path}/base/template_helpers.h

    ${header_path}/tools/Serializer.h
    ${header_path}/tools/SerializerJSON.h
    ${header_path}/tools/SerializerINI.h
    ${header_path}/tools/JSONReader.h

    ${header_path}/property/property_declaration.h
    ${header_path}/property/TypeConverter.h
    ${header_path}/property/TypeConverter.hpp
    ${header_path}/property/AbstractProperty.h
    ${header_path}/property/AbstractProperty.hpp
    ${header_path}/property/AbstractValueProperty.h
    ${header_path}/property/AbstractTypedProperty.h
    ${header_path}/property/AbstractTypedProperty.hpp
    ${header_path}/property/AbstractArrayProperty.h
    ${header_path}/property/AbstractArrayProperty.hpp
    ${header_path}/property/AbstractCollection.h
    ${header_path}/property/AbstractAccessor.h
    ${header_path}/property/Accessor.h
    ${header_path}/property/Accessor.hpp
    ${header_path}/property/AccessorGetSet.h
    ${header_path}/property/AccessorGetSet.hpp
    ${header_path}/property/AccessorValue.h
    ${header_path}/property/AccessorValue.hpp
    ${header_path}/property/ArrayAccessor.h
    ${header_path}/property/ArrayAccessor.hpp
    ${header_path}/property/ArrayAccessorGetSet.h
    ${header_path}/property/ArrayAccessorGetSet.hpp
    ${header_path}/property/ArrayAccessorValue.h
    ${header_path}/property/ArrayAccessorValue.hpp
    ${header_path}/property/PropertyEnum.h
    ${header_path}/property/PropertyEnum.hpp
    ${header_path}/property/PropertyArray.h
    ${header_path}/property/PropertyArray.hpp
    ${header_path}/property/PropertyBool.h
    ${header_path}/property/PropertyBool.hpp
    ${header_path}/property/PropertyColor.h
    ${header_path}/property/PropertyColor.hpp
    ${header_path}/property/PropertyFilePath.h
    ${header_path}/property/PropertyFilePath.hpp
    ${header_path}/property/PropertyFloatingPoint.h
    ${header_path}/property/PropertyFloatingPoint.hpp
    ${header_path}/property/PropertySignedIntegral.h
    ${header_path}/property/PropertySignedIntegral.hpp
    ${header_path}/property/PropertyString.h
    ${header_path}/property/PropertyString.hpp
    ${header_path}/property/PropertyUnsignedIntegral.h
    ${header_path}/property/PropertyUnsignedIntegral.hpp
    ${header_path}/property/AbstractNumberProperty.h
    ${header_path}/property/AbstractNumberProperty.hpp
    ${header_path}/property/AbstractBooleanInterface.h
    ${header_path}/property/AbstractStringInterface.h
    ${header_path}/property/AbstractColorInterface.h
    ${header_path}/property/AbstractFloatingPointInterface.h
    ${header_path}/property/AbstractSignedIntegralInterface.h
    ${header_path}/property/AbstractUnsignedIntegralInterface.h
    ${header_path}/property/AbstractEnumInterface.h
    ${header_path}/property/AbstractVisitor.h
    ${header_path}/property/AbstractVisitor.hpp
    ${header_path}/property/Visitor.h
    ${header_path}/property/Property.h
    ${header_path}/property/Property.hpp
    ${header_path}/property/PropertyGroup.h
    ${header_path}/property/PropertyGroup.hpp

    ${header_path}/function/Function.h
    ${header_path}/function/Function.hpp

    ${header_path}/variant/Variant.h
    ${header_path}/variant/Variant.hpp

    ${header_path}/Object.h
)

set(sources
    ${source_path}/base/util.cpp
    ${source_path}/base/Color.cpp
    ${source_path}/base/FilePath.cpp

    ${source_path}/tools/Serializer.cpp
    ${source_path}/tools/SerializerJSON.cpp
    ${source_path}/tools/SerializerINI.cpp
    ${source_path}/tools/JSONReader.cpp

    ${source_path}/property/AbstractAccessor.cpp
    ${source_path}/property/AbstractProperty.cpp
    ${source_path}/property/AbstractValueProperty.cpp
    ${source_path}/property/AbstractCollection.cpp
    ${source_path}/property/AbstractBooleanInterface.cpp
    ${source_path}/property/AbstractStringInterface.cpp
    ${source_path}/property/AbstractColorInterface.cpp
    ${source_path}/property/AbstractFloatingPointInterface.cpp
    ${source_path}/property/AbstractSignedIntegralInterface.cpp
    ${source_path}/property/AbstractUnsignedIntegralInterface.cpp
    ${source_path}/property/AbstractEnumInterface.cpp
    ${source_path}/property/AbstractVisitor.cpp
    ${source_path}/property/PropertyGroup.cpp

    ${source_path}/function/Function.cpp

    ${source_path}/variant/Variant.cpp

    ${source_path}/Object.cpp
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
