
set(target propertyguiexample)
message(STATUS "Example ${target}")

#
# External libraries
#

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

#
# Includes
#

include_directories(
)

include_directories(
    BEFORE
    ${CMAKE_SOURCE_DIR}/source/signalzeug/include
    ${CMAKE_SOURCE_DIR}/source/reflectionzeug/include
    ${CMAKE_SOURCE_DIR}/source/propertyguizeug/include
)

#
# Libraries
#

set(libs
    propertyguizeug
	reflectionzeug
	signalzeug
    # this target link libraries somehow fixes the include directories for used qt modules.
    # (not nice! since it obfuscates the common cmake way to link 3rdp libraries..., 
    #  but seems to be intended by qt: http://qt-project.org/doc/qt-5/cmake-manual.html)
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

#
# Compiler definitions
#

#
# Sources
#

set(sources
    main.cpp
    Switch.h
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
