
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
    ${header_path}/property_declaration.h

    ${header_path}/base/util.h
    ${header_path}/base/util.hpp
    ${header_path}/base/Color.h
    ${header_path}/base/FilePath.h

    ${header_path}/type/specialization_helpers.h
    ${header_path}/type/AbstractProperty.h
    ${header_path}/type/AbstractProperty.hpp
    ${header_path}/type/AbstractPropertyValue.h
    ${header_path}/type/AbstractPropertyValue.hpp
    ${header_path}/type/AbstractPropertyArray.h
    ${header_path}/type/AbstractPropertyArray.hpp
    ${header_path}/type/AbstractCollection.h
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
    ${header_path}/type/Property.h
    ${header_path}/type/Property.hpp
    ${header_path}/type/PropertyEnum.h
    ${header_path}/type/PropertyEnum.hpp
    ${header_path}/type/PropertyArray.h
    ${header_path}/type/PropertyArray.hpp
    ${header_path}/type/PropertyBool.h
    ${header_path}/type/PropertyBool.hpp
    ${header_path}/type/PropertyClass.h
    ${header_path}/type/PropertyClass.hpp
    ${header_path}/type/PropertyColor.h
    ${header_path}/type/PropertyColor.hpp
    ${header_path}/type/PropertyFilePath.h
    ${header_path}/type/PropertyFilePath.hpp
    ${header_path}/type/PropertyFloatingPoint.h
    ${header_path}/type/PropertyFloatingPoint.hpp
    ${header_path}/type/PropertySignedIntegral.h
    ${header_path}/type/PropertySignedIntegral.hpp
    ${header_path}/type/PropertyString.h
    ${header_path}/type/PropertyString.hpp
    ${header_path}/type/PropertyUnsignedIntegral.h
    ${header_path}/type/PropertyUnsignedIntegral.hpp
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

    ${header_path}/function/template_helpers.h
    ${header_path}/function/Function.h

    ${header_path}/tools/JSON.h
    ${header_path}/tools/JSONReader.h

    ${header_path}/PropertyGroup.h
    ${header_path}/PropertyGroup.hpp
    ${header_path}/Property.h
    ${header_path}/Object.h
    ${header_path}/Variant.h
    ${header_path}/Variant.hpp
)

set(sources
    ${source_path}/base/util.cpp
    ${source_path}/base/Color.cpp
    ${source_path}/base/FilePath.cpp

    ${source_path}/type/AbstractAccessor.cpp
    ${source_path}/type/AbstractProperty.cpp
    ${source_path}/type/AbstractCollection.cpp
    ${source_path}/type/AbstractBooleanInterface.cpp
    ${source_path}/type/AbstractStringInterface.cpp
    ${source_path}/type/AbstractColorInterface.cpp
    ${source_path}/type/AbstractFloatingPointInterface.cpp
    ${source_path}/type/AbstractSignedIntegralInterface.cpp
    ${source_path}/type/AbstractUnsignedIntegralInterface.cpp
    ${source_path}/type/AbstractEnumInterface.cpp
    ${source_path}/type/AbstractVisitor.cpp
    ${source_path}/type/PropertyBool.cpp
    ${source_path}/type/PropertyString.cpp
    ${source_path}/type/PropertyColor.cpp
    ${source_path}/type/PropertyFilePath.cpp

    ${source_path}/tools/JSON.cpp
    ${source_path}/tools/JSONReader.cpp

    ${source_path}/PropertyGroup.cpp
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
