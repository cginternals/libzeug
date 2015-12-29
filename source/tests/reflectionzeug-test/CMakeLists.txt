
# 
# Executable name and options
# 

# Target name
set(target reflectionzeug-test)
message(STATUS "Test ${target}")


# 
# Sources
# 

set(sources
    main.cpp
    # Color_test.cpp
    
    propertyInstanciationTests/PropertyInstanciationBool_test.cpp
    propertyInstanciationTests/PropertyInstanciationFloat_test.cpp
    propertyInstanciationTests/PropertyInstanciationDouble_test.cpp
    propertyInstanciationTests/PropertyInstanciationInt8_T_test.cpp
    propertyInstanciationTests/PropertyInstanciationUint8_T_test.cpp
    propertyInstanciationTests/PropertyInstanciationInt16_T_test.cpp
    propertyInstanciationTests/PropertyInstanciationUint16_T_test.cpp
    propertyInstanciationTests/PropertyInstanciationInt32_T_test.cpp
    propertyInstanciationTests/PropertyInstanciationUint32_T_test.cpp
    propertyInstanciationTests/PropertyInstanciationInt64_T_test.cpp
    propertyInstanciationTests/PropertyInstanciationUint64_T_test.cpp
    propertyInstanciationTests/PropertyInstanciationString_test.cpp
    propertyInstanciationTests/PropertyInstanciationVariant_test.cpp
    propertyInstanciationTests/PropertyInstanciationBoolArray_test.cpp
    propertyInstanciationTests/PropertyInstanciationFloatArray_test.cpp
    propertyInstanciationTests/PropertyInstanciationDoubleArray_test.cpp
    propertyInstanciationTests/PropertyInstanciationInt8_TArray_test.cpp
    propertyInstanciationTests/PropertyInstanciationUint8_TArray_test.cpp
    propertyInstanciationTests/PropertyInstanciationInt16_TArray_test.cpp
    propertyInstanciationTests/PropertyInstanciationUint16_TArray_test.cpp
    propertyInstanciationTests/PropertyInstanciationInt32_TArray_test.cpp
    propertyInstanciationTests/PropertyInstanciationUint32_TArray_test.cpp
    propertyInstanciationTests/PropertyInstanciationInt64_TArray_test.cpp
    propertyInstanciationTests/PropertyInstanciationUint64_TArray_test.cpp
    propertyInstanciationTests/PropertyInstanciationStringArray_test.cpp
    propertyInstanciationTests/PropertyInstanciationVariantArray_test.cpp
)


# 
# Create executable
# 

# Build executable
add_executable(${target}
    ${sources}
)

# Create namespaced alias
add_executable(${META_PROJECT_NAME}::${target} ALIAS ${target})


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
    ${DEFAULT_INCLUDE_DIRECTORIES}
    ${PROJECT_BINARY_DIR}/source/include
)


# 
# Libraries
# 

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LIBRARIES}
    ${META_PROJECT_NAME}::reflectionzeug
    gmock-dev
)


# 
# Compile definitions
# 

target_compile_definitions(${target}
    PRIVATE
    ${DEFAULT_COMPILE_DEFINITIONS}
)


# 
# Compile options
# 

target_compile_options(${target}
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
)


# 
# Linker options
# 

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
)
