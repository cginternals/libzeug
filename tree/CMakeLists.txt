CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../cmake_modules")

# TreeZeug

PROJECT(TreeZeug)

INCLUDE(PlatformSetup)

SET(tree_target treezeug)

INCLUDE_DIRECTORIES("include")

SET(sources
	src/Attribute.cpp
	src/AttributeMap.cpp
	src/LinearizedTree.cpp
	src/Tree.cpp
)

SET(headers
	include/Attribute.h
	include/AttributeMap.h
	include/LinearizedTree.h
	include/Tree.h
)

ADD_LIBRARY(${tree_target} SHARED ${sources} ${headers})

# TreeImportZeug

PROJECT(TreeImportZeug)

INCLUDE(PlatformSetup)

FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Xml REQUIRED)

SET(tree_import_target treeimportzeug)

INCLUDE_DIRECTORIES("include")

SET(sources
	src/import/CityGMLStrategy.cpp
	src/import/SoftwareSystemStrategy.cpp
	src/import/TreeStrategy.cpp
	src/import/TreeXmlParser.cpp
	src/import/TreeXmlParserStrategy.cpp
)

SET(headers
	include/import/CityGMLStrategy.h
	include/import/SoftwareSystemStrategy.h
	include/import/TreeStrategy.h
	include/import/TreeXmlParser.h
	include/import/TreeXmlParserStrategy.h
)

ADD_LIBRARY(${tree_import_target} SHARED ${sources} ${headers})

TARGET_LINK_LIBRARIES(${tree_import_target}
	${tree_target}
)

QT5_USE_MODULES(${tree_import_target} Xml)
