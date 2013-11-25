
# Target
set(target treeimportzeug)
message(STATUS "lib ${target}")

# Find externals
find_package(Qt5Core)
find_package(Qt5Sql)
find_package(Qt5Xml)

set(CMAKE_AUTOMOC ON)

# Libraries
set(libs
    treezeug
)

# Definitions
add_definitions("-DTREEIMPORTZEUG_EXPORTS")

# Sources
set(header_path "${LIBZEUG_SOURCE_DIR}/include/treeimportzeug")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}")

set(headers
    ${header_path}/treeimportzeug.h

    ${header_path}/ChangesStrategy.h
    ${header_path}/CityGMLStrategy.h
    ${header_path}/SDStrategy.h
    ${header_path}/SoftwareSystemStrategy.h
    ${header_path}/TreeImport.h
    ${header_path}/TreeSqliteParser.h
    ${header_path}/TreeSqliteParserStrategy.h
    ${header_path}/TreeStrategy.h
    ${header_path}/TreeXmlParser.h
    ${header_path}/TreeXmlParserStrategy.h
)

set(sources
    ${source_path}/ChangesStrategy.cpp
    ${source_path}/CityGMLStrategy.cpp
    ${source_path}/SDStrategy.cpp
    ${source_path}/SoftwareSystemStrategy.cpp
    ${source_path}/TreeImport.cpp
    ${source_path}/TreeSqliteParser.cpp
    ${source_path}/TreeSqliteParserStrategy.cpp
    ${source_path}/TreeStrategy.cpp
    ${source_path}/TreeXmlParser.cpp
    ${source_path}/TreeXmlParserStrategy.cpp
)

# Group source files
set(treeimportzeug_header_group "Header Files (API)")
set(treeimportzeug_source_group "Source Files")
source_group_by_path(${header_path} "\\\\.h$|\\\\.hpp$" 
    ${treeimportzeug_header_group} ${headers})
source_group_by_path(${source_path} "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${treeimportzeug_source_group} ${sources})

# Build library
if(OPTION_BUILD_STATIC)
    add_library(${target} ${headers} ${sources})
else()
    add_library(${target} SHARED ${headers} ${sources})
endif()

qt5_use_modules(${target} Core Xml Sql)
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
