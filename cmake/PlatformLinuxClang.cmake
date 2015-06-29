message(STATUS "Configuring for platform Linux/Clang.")


# Enable C++11 support

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

include_directories("/usr/include/c++/v1/")

set(LINUX_COMPILE_DEFS
    LINUX                     # Linux system
    PIC                       # Position-independent code
    _REENTRANT                # Reentrant code
)
set(DEFAULT_COMPILE_DEFS_DEBUG
    ${LINUX_COMPILE_DEFS}
    _DEBUG                    # Debug build
)
set(DEFAULT_COMPILE_DEFS_RELEASE
    ${LINUX_COMPILE_DEFS}
    NDEBUG                    # Release build
)

set(LINUX_COMPILE_FLAGS 
      
      -fexceptions  # -> enable exceptions
      -pthread      # -> use pthread library
    # -no-rtti      # -> disable c++ rtti
      -pipe         # -> use pipes
      -Wall         # -> 
      -Wextra       # -> 
      -Werror       # ->
      -fPIC         # -> use position independent code

      -ftemplate-backtrace-limit=0

      -Wno-unknown-warning-option
      -Wno-reinterpret-base-class 
      -Wno-overloaded-virtual
      -Wno-inconsistent-missing-override

      -Wreturn-type
      -Wno-unused-parameter
      -Wno-unused-variable
      -Wno-unused-but-set-variable

    # -Werror=return-type -> missing returns in functions and methods are handled as errors which stops the compilation
    # -Wshadow      # -> e.g. when a parameter is named like a member, too many warnings, disabled for now
)

set(DEFAULT_COMPILE_FLAGS
    ${LINUX_COMPILE_FLAGS}
    $<$<CONFIG:Debug>:   
    >
    $<$<CONFIG:Release>: 
    >
)

set(LINUX_LINKER_FLAGS "-pthread")

set(DEFAULT_LINKER_FLAGS_RELEASE ${LINUX_LINKER_FLAGS})
set(DEFAULT_LINKER_FLAGS_DEBUG ${LINUX_LINKER_FLAGS})
set(DEFAULT_LINKER_FLAGS ${LINUX_LINKER_FLAGS})

# Add platform specific libraries for linking
set(EXTRA_LIBS "")
