
# Target
set(target threadingzeug)
message(STATUS "lib ${target}")

# Find externals
if(OPTION_USE_OPENMP)
	find_package(OpenMP QUIET)
	
	if (OPENMP_FOUND)
		message(STATUS "Use OpenMP for threading.")
	else()
		message(WARNING "OPTION_USE_OPENMP is set to ON, but OpenMP couldn't been found.")
		message(WARNING "Defaulting to C++11 threading.")
	endif()
endif()

# Libraries
set(libs
)

# Definitions
add_definitions("-DTHREADINGZEUG_EXPORTS")

# Sources
set(header_path "${LIBZEUG_SOURCE_DIR}/include/threadingzeug")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}")

set(headers
    ${header_path}/threadingzeug.h
    
    ${header_path}/parallelfor.h
    ${header_path}/parallelfor.hpp
)

set(sources
    ${source_path}/parallelfor.cpp
)

# Group source files
set(threadingzeug_header_group "Header Files (API)")
set(threadingzeug_source_group "Source Files")
source_group_by_path(${header_path} "\\\\.h$|\\\\.hpp$" 
    ${threadingzeug_header_group} ${headers})
source_group_by_path(${source_path} "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${threadingzeug_source_group} ${sources})

#Additional Flags
if(OPTION_USE_OPENMP AND OPENMP_FOUND)
    add_definitions("-DUSE_OPENMP")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# Build library
if(OPTION_BUILD_STATIC)
    add_library(${target} ${headers} ${sources})
else()
    add_library(${target} SHARED ${headers} ${sources})
endif()
target_link_libraries(${target} ${libs})
set_target_properties(${target}
    PROPERTIES
    LINKER_LANGUAGE CXX
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}"
    INCLUDE_PATH                "${LIBZEUG_SOURCE_DIR}/include")

# Deployment
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN}
    LIBRARY DESTINATION ${INSTALL_SHARED}
    ARCHIVE DESTINATION ${INSTALL_LIB}
)
