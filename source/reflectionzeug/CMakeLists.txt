
# 
# External dependencies
# 

set(ADDITIONAL_LIBRARIES)
set(ADDITIONAL_INCLUDES)
if(NOT OPTION_BUILD_WITH_STD_REGEX)
    find_package(Boost COMPONENTS regex REQUIRED)
    
    if (Boost_FOUND)
        message(STATUS "Use Boost for regex.")
        
        set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} ${Boost_LIBRARIES})
        set(ADDITIONAL_INCLUDES ${ADDITIONAL_INCLUDES} ${Boost_INCLUDE_DIRS})
    else()
        message(WARNING "OPTION_BUILD_WITH_STD_REGEX is set to Off: Boost not found.")
        message(WARNING "Defaulting to C++11 regex.")
    endif()
endif()


# 
# Library name and options
# 

# Target name
set(target reflectionzeug)

# Exit here if required dependencies are not met
message(STATUS "Lib ${target}")

# Set API export file and macro
string(TOUPPER ${target} target_upper)
set(export_file  "include/${target}/${target}_api.h")
set(export_macro "${target_upper}_API")


# 
# Sources
# 

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path  "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
    ${include_path}/base/Color.h
    ${include_path}/base/FilePath.h
    ${include_path}/base/template_helpers.h

    ${include_path}/tools/Serializer.h
    ${include_path}/tools/SerializerJSON.h
    ${include_path}/tools/SerializerINI.h
    ${include_path}/tools/JSONReader.h

    ${include_path}/property/property_declaration.h
    ${include_path}/property/TypeConverter.h
    ${include_path}/property/TypeConverter.hpp
    ${include_path}/property/AbstractProperty.h
    ${include_path}/property/AbstractProperty.hpp
    ${include_path}/property/AbstractValueProperty.h
    ${include_path}/property/AbstractTypedProperty.h
    ${include_path}/property/AbstractTypedProperty.hpp
    ${include_path}/property/AbstractArrayProperty.h
    ${include_path}/property/AbstractArrayProperty.hpp
    ${include_path}/property/AbstractCollection.h
    ${include_path}/property/AbstractAccessor.h
    ${include_path}/property/Accessor.h
    ${include_path}/property/Accessor.hpp
    ${include_path}/property/AccessorGetSet.h
    ${include_path}/property/AccessorGetSet.hpp
    ${include_path}/property/AccessorValue.h
    ${include_path}/property/AccessorValue.hpp
    ${include_path}/property/ArrayAccessor.h
    ${include_path}/property/ArrayAccessor.hpp
    ${include_path}/property/ArrayAccessorGetSet.h
    ${include_path}/property/ArrayAccessorGetSet.hpp
    ${include_path}/property/ArrayAccessorValue.h
    ${include_path}/property/ArrayAccessorValue.hpp
    ${include_path}/property/PropertyEnum.h
    ${include_path}/property/PropertyEnum.hpp
    ${include_path}/property/PropertyArray.h
    ${include_path}/property/PropertyArray.hpp
    ${include_path}/property/PropertyBool.h
    ${include_path}/property/PropertyBool.hpp
    ${include_path}/property/PropertyColor.h
    ${include_path}/property/PropertyColor.hpp
    ${include_path}/property/PropertyFilePath.h
    ${include_path}/property/PropertyFilePath.hpp
    ${include_path}/property/PropertyFloatingPoint.h
    ${include_path}/property/PropertyFloatingPoint.hpp
    ${include_path}/property/PropertySignedIntegral.h
    ${include_path}/property/PropertySignedIntegral.hpp
    ${include_path}/property/PropertyString.h
    ${include_path}/property/PropertyString.hpp
    ${include_path}/property/PropertyUnsignedIntegral.h
    ${include_path}/property/PropertyUnsignedIntegral.hpp
    ${include_path}/property/PropertyVariant.h
    ${include_path}/property/PropertyVariant.hpp
    ${include_path}/property/AbstractNumberProperty.h
    ${include_path}/property/AbstractNumberProperty.hpp
    ${include_path}/property/AbstractBooleanInterface.h
    ${include_path}/property/AbstractStringInterface.h
    ${include_path}/property/AbstractColorInterface.h
    ${include_path}/property/AbstractFloatingPointInterface.h
    ${include_path}/property/AbstractSignedIntegralInterface.h
    ${include_path}/property/AbstractUnsignedIntegralInterface.h
    ${include_path}/property/AbstractEnumInterface.h
    ${include_path}/property/AbstractVariantInterface.h
    ${include_path}/property/AbstractVisitor.h
    ${include_path}/property/AbstractVisitor.hpp
    ${include_path}/property/Visitor.h
    ${include_path}/property/Property.h
    ${include_path}/property/Property.hpp
    ${include_path}/property/PropertyGroup.h
    ${include_path}/property/PropertyGroup.hpp

    ${include_path}/function/Function.h
    ${include_path}/function/Function.hpp

    ${include_path}/variant/Variant.h
    ${include_path}/variant/Variant.hpp

    ${include_path}/Object.h
)

set(sources
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
    ${source_path}/property/AbstractVariantInterface.cpp
    ${source_path}/property/AbstractVisitor.cpp
    ${source_path}/property/PropertyGroup.cpp

    ${source_path}/function/Function.cpp

    ${source_path}/variant/Variant.cpp

    ${source_path}/Object.cpp
)

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${include_path} "\\\\.h$|\\\\.hpp$" 
    ${header_group} ${headers})
source_group_by_path(${source_path}  "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${source_group} ${sources})


# 
# Create library
# 

# Build library
add_library(${target}
    ${sources}
    ${headers}
)

# Create namespaced alias
add_library(${META_PROJECT_NAME}::${target} ALIAS ${target})

# Export library for downstream projects
export(TARGETS ${target} NAMESPACE ${META_PROJECT_NAME}:: FILE ${PROJECT_BINARY_DIR}/cmake/${target}/${target}-export.cmake)

# Create API export header
generate_export_header(${target}
    EXPORT_FILE_NAME  ${export_file}
    EXPORT_MACRO_NAME ${export_macro}
)


# 
# Project options
# 

set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
    FOLDER "${IDE_FOLDER}"
)


# 
# Include directories
# 

target_include_directories(${target}
    PRIVATE
    ${PROJECT_BINARY_DIR}/source/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include
    ${ADDITIONAL_INCLUDES}

    PUBLIC
    ${DEFAULT_INCLUDE_DIRECTORIES}

    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)


# 
# Libraries
# 

target_link_libraries(${target}
    PRIVATE
    ${ADDITIONAL_LIBRARIES}
    ${META_PROJECT_NAME}::loggingzeug

    PUBLIC
    ${DEFAULT_LIBRARIES}
    ${META_PROJECT_NAME}::signalzeug
    ${META_PROJECT_NAME}::stringzeug

    INTERFACE
)


# 
# Compile definitions
# 

target_compile_definitions(${target}
    PRIVATE
    $<$<BOOL:${OPTION_BUILD_WITH_STD_REGEX}>:USE_STD_REGEX>

    PUBLIC
    $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:${target_upper}_STATIC_DEFINE>
    ${DEFAULT_COMPILE_DEFINITIONS}

    INTERFACE
)


# 
# Compile options
# 

target_compile_options(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}

    INTERFACE
)


# 
# Linker options
# 

target_link_libraries(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_LINKER_OPTIONS}

    INTERFACE
)


# 
# Deployment
# 

# Library
install(TARGETS ${target}
    EXPORT  "${target}-export"            COMPONENT dev
    RUNTIME DESTINATION ${INSTALL_BIN}    COMPONENT runtime
    LIBRARY DESTINATION ${INSTALL_SHARED} COMPONENT runtime
    ARCHIVE DESTINATION ${INSTALL_LIB}    COMPONENT dev
)

# Header files
install(DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE}
    COMPONENT dev
)

# Generated header files
install(DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE}
    COMPONENT dev
)

# CMake config
install(EXPORT ${target}-export
    NAMESPACE   ${META_PROJECT_NAME}::
    DESTINATION ${INSTALL_CMAKE}/${target}
    COMPONENT   dev
)
