cmake_minimum_required(VERSION 2.8)

# Project
project(propertyexample)
set(target propertyexample)

# Include directories
include_directories(
	${LIBZEUG_INCLUDE_DIR}
  include
)

# Libraries
set(libs
	propertyzeug
)

# Definitions
#add_definitions("-D...")

# Sources
set(header_path "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(headers
)
set(sources
	${source_path}/main.cpp
)

# Group source files
set(header_group "Property Example Headers")
set(source_group "Property Example Sources")
source_group_by_path(${header_path} "\\\\.h$|\\\\.hpp$" 
    ${header_group} ${headers})
source_group_by_path(${source_path} "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${source_group} ${sources})

# Build executable
add_executable(${target} ${headers} ${sources})
target_link_libraries(${target} ${libs})
qt5_use_modules(${target} Core)

# Deployment
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_EXAMPLES}
#    LIBRARY DESTINATION ${INSTALL_SHARED}
#    ARCHIVE DESTINATION ${INSTALL_LIB}
)
