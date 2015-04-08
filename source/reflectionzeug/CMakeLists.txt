
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
    
    ${header_path}/AbstractArrayValue.h
    ${header_path}/AbstractProperty.h
    ${header_path}/AbstractProperty.hpp
    ${header_path}/AbstractPropertyCollection.h
    ${header_path}/AbstractPropertyVisitor.h
    ${header_path}/AbstractPropertyVisitor.hpp
    ${header_path}/AbstractValue.h
    ${header_path}/AbstractValueProperty.h
    ${header_path}/AccessorArrayValue.h
    ${header_path}/AccessorArrayValue.hpp
    ${header_path}/AccessorValue.h
    ${header_path}/AccessorValue.hpp
    ${header_path}/ArrayProperty.h
    ${header_path}/ArrayProperty.hpp
    ${header_path}/BoolProperty.h
    ${header_path}/BoolProperty.hpp
    ${header_path}/ClassProperty.h
    ${header_path}/ClassProperty.hpp
    ${header_path}/Color.h
    ${header_path}/ColorProperty.h
    ${header_path}/ColorProperty.hpp
    ${header_path}/ColorPropertyInterface.h
    ${header_path}/EnumProperty.h
    ${header_path}/EnumProperty.hpp
    ${header_path}/EnumPropertyInterface.h
    ${header_path}/FilePath.h
    ${header_path}/FilePathProperty.h
    ${header_path}/FilePathProperty.hpp
    ${header_path}/FloatingPointProperty.h
    ${header_path}/FloatingPointProperty.hpp
    ${header_path}/FloatingPointPropertyInterface.h
    ${header_path}/Function.h
    ${header_path}/NumberProperty.h
    ${header_path}/NumberProperty.hpp
    ${header_path}/Object.h
    ${header_path}/Property.h
    ${header_path}/PropertyDeserializer.h
    ${header_path}/PropertyGroup.h
    ${header_path}/PropertyGroup.hpp
    ${header_path}/PropertySerializer.h
    ${header_path}/PropertyVisitor.h
    ${header_path}/SignedIntegralProperty.h
    ${header_path}/SignedIntegralProperty.hpp
    ${header_path}/SignedIntegralPropertyInterface.h
    ${header_path}/StandardPropertyVisitor.h
    ${header_path}/StoredArrayValue.h
    ${header_path}/StoredArrayValue.hpp
    ${header_path}/StoredValue.h
    ${header_path}/StoredValue.hpp
    ${header_path}/StringProperty.h
    ${header_path}/StringProperty.hpp
    ${header_path}/StringPropertyInterface.h
    ${header_path}/TemplateHelper.h
    ${header_path}/UnsignedIntegralProperty.h
    ${header_path}/UnsignedIntegralProperty.hpp
    ${header_path}/UnsignedIntegralPropertyInterface.h
    ${header_path}/ValueProperty.h
    ${header_path}/ValueProperty.hpp
    ${header_path}/Variant.h
    ${header_path}/Variant.hpp
    ${header_path}/VariantConverterRegistry.h
    ${header_path}/VariantConverterRegistry.hpp
    ${header_path}/VariantConverterInit.h
    ${header_path}/VariantHolder.h
    ${header_path}/VariantHolder.hpp
    ${header_path}/property_declaration.h
    ${header_path}/specialization_helpers.h
    ${header_path}/util.h
    ${header_path}/util.hpp
    ${header_path}/extensions/GlmProperties.hpp

    ${header_path}/new/AbstractTyped.h
    ${header_path}/new/AbstractTyped.hpp
    ${header_path}/new/AbstractTypedArray.h
    ${header_path}/new/AbstractTypedArray.hpp
    ${header_path}/new/Accessor.h
    ${header_path}/new/Accessor.hpp
    ${header_path}/new/AccessorGetSet.h
    ${header_path}/new/AccessorGetSet.hpp
    ${header_path}/new/AccessorValue.h
    ${header_path}/new/AccessorValue.hpp
    ${header_path}/new/ArrayAccessor.h
    ${header_path}/new/ArrayAccessor.hpp
    ${header_path}/new/ArrayAccessorGetSet.h
    ${header_path}/new/ArrayAccessorGetSet.hpp
    ${header_path}/new/ArrayAccessorValue.h
    ${header_path}/new/ArrayAccessorValue.hpp
    ${header_path}/new/Convertible.h
    ${header_path}/new/Convertible.hpp
    ${header_path}/new/Typed.h
    ${header_path}/new/Typed.hpp
    ${header_path}/new/TypedEnum.h
    ${header_path}/new/TypedEnum.hpp
    ${header_path}/new/TypedArray.h
    ${header_path}/new/TypedArray.hpp
    ${header_path}/new/TypedBool.h
    ${header_path}/new/TypedBool.hpp
    ${header_path}/new/TypedClass.h
    ${header_path}/new/TypedClass.hpp
    ${header_path}/new/TypedColor.h
    ${header_path}/new/TypedColor.hpp
    ${header_path}/new/TypedFilePath.h
    ${header_path}/new/TypedFilePath.hpp
    ${header_path}/new/TypedFloatingPoint.h
    ${header_path}/new/TypedFloatingPoint.hpp
    ${header_path}/new/TypedSignedIntegral.h
    ${header_path}/new/TypedSignedIntegral.hpp
    ${header_path}/new/TypedString.h
    ${header_path}/new/TypedString.hpp
    ${header_path}/new/TypedUnsignedIntegral.h
    ${header_path}/new/TypedUnsignedIntegral.hpp
)

set(sources
    ${source_path}/AbstractProperty.cpp
    ${source_path}/AbstractPropertyCollection.cpp
    ${source_path}/AbstractPropertyVisitor.cpp
    ${source_path}/AbstractValueProperty.cpp
    ${source_path}/BoolProperty.cpp
    ${source_path}/Color.cpp
    ${source_path}/ColorProperty.cpp
    ${source_path}/ColorPropertyInterface.cpp
    ${source_path}/EnumPropertyInterface.cpp
    ${source_path}/FilePath.cpp
    ${source_path}/FilePathProperty.cpp
    ${source_path}/FloatingPointPropertyInterface.cpp
    ${source_path}/Object.cpp
    ${source_path}/PropertyDeserializer.cpp
    ${source_path}/PropertyGroup.cpp
    ${source_path}/PropertySerializer.cpp
    ${source_path}/StringProperty.cpp
    ${source_path}/StringPropertyInterface.cpp
    ${source_path}/SignedIntegralPropertyInterface.cpp
    ${source_path}/UnsignedIntegralPropertyInterface.cpp
    ${source_path}/util.cpp
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
