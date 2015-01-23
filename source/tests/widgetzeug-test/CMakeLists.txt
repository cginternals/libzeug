
set(target widgetzeug-test)
message(STATUS "Test ${target}")

# External libraries

find_package(Qt5Core    5.1 REQUIRED)
find_package(Qt5Gui     5.1 REQUIRED)
find_package(Qt5Widgets 5.1 REQUIRED)

# Includes

include_directories(
)

include_directories(
    BEFORE
    ${CMAKE_SOURCE_DIR}/source/widgetzeug/include
    ${CMAKE_SOURCE_DIR}/source/reflectionzeug/include
    ${CMAKE_SOURCE_DIR}/source/signalzeug/include
)


# Libraries

set(libs
    ${GMOCK_LIBRARIES}
    ${GTEST_LIBRARIES}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    reflectionzeug
    signalzeug
    widgetzeug
)


# Sources

set(sources
    main.cpp
    ColorGradient_test.cpp
    ColorGradientInterpolation_test.cpp
    ColorGradientProperty_test.cpp
)


# Build executable

add_executable(${target} ${sources})

target_link_libraries(${target} ${libs})


if(MSVC)
    # -> msvc14 : declaration hides class member (problem in qt)
    set(DEFAULT_COMPILE_FLAGS ${DEFAULT_COMPILE_FLAGS} /wd4458)
endif()

target_compile_options(${target} PRIVATE ${DEFAULT_COMPILE_FLAGS})

set_target_properties(${target}
    PROPERTIES
    LINKER_LANGUAGE              CXX
    FOLDER                      "${IDE_FOLDER}"
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")
