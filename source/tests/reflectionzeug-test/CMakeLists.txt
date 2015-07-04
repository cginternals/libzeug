
set(target reflectionzeug-test)
message(STATUS "Test ${target}")

# Generate Property Instanciation Tests
set(testdir ${CMAKE_SOURCE_DIR}/source/tests/reflectionzeug-test)
set(filelist ${testdir}/instanciationTestsFiles.txt)
# execute_process(COMMAND python ${testdir}/generateInstanciationTests.py ${testdir} ${filelist})
add_custom_target("generatePropertyTests" COMMAND python ${testdir}/generateInstanciationTests.py ${testdir} ${filelist})

# External libraries

# ...

# Includes

include_directories(
)

include_directories(
    BEFORE
    ${CMAKE_SOURCE_DIR}/source/reflectionzeug/include
    ${CMAKE_SOURCE_DIR}/source/signalzeug/include
)


# Libraries

set(libs
    ${GMOCK_LIBRARIES}
    ${GTEST_LIBRARIES}
    reflectionzeug
    signalzeug
)


# Sources

set(sources
    main.cpp
    # Color_test.cpp
)

if(EXISTS ${filelist})
    FILE(READ ${filelist} contents)
    STRING(REGEX REPLACE ";" "\\\\;" contents "${contents}")
    STRING(REGEX REPLACE "\n" ";" contents "${contents}")
    set(sources
        ${sources}
        ${contents}
    )
endif()


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
