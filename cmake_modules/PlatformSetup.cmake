# check if x64 and provide this information (used for, e.g., freeglut)

set(X64 OFF)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(X64 ON)
endif()

# check for linux

if(UNIX AND NOT APPLE)
    set(LINUX 1)
endif()

if(MSVC)
    message(STATUS "Configuring for platform Windows/MSVC.")
    include(PlatformWindowsMSVC)
elseif(WIN32 AND CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "Configuring for platform Windows/GCC.")
    include(PlatformWindowsGCC)
elseif(LINUX AND CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "Configuring for platform Linux/GCC.")
    include(PlatformLinuxGCC)
elseif(APPLE)
    message(STATUS "Configuring for platform MacOS.")
    include(PlatformMacOS)
else()
    # TODO configure for apple        
    message(WARNING "Unsupported platform/compiler combination")
endif()
