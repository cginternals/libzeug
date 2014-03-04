
set(target propertyexample)
message(STATUS "Example ${target}")

#
# External libraries
#

#
# Includes
#

include_directories(
)

include_directories(
    BEFORE
    ${CMAKE_SOURCE_DIR}/source/signalzeug/include
    ${CMAKE_SOURCE_DIR}/source/reflectionzeug/include
)

#
# Libraries
#

set(libs
    reflectionzeug
)

#
# Compiler definitions
#

#
# Sources
#

set(sources
    main.cpp

    PropertyExtension.h
    SomeObject.cpp
    SomeObject.h
)

#
# Build executable
#

add_executable(${target} ${sources})

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
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")

#
# Deployment
#

install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_EXAMPLES}
    LIBRARY DESTINATION ${INSTALL_SHARED}
    ARCHIVE DESTINATION ${INSTALL_LIB}
)
