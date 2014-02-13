
# Generate meta-header
configure_file(libzeug-version.h.in ${CMAKE_CURRENT_BINARY_DIR}/libzeug-version.h)

# We do NOT want to deploy this header (at least not for binary packages)
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/template/libzeug-version.h DESTINATION ${INSTALL_INCLUDE}/template)

# Include directories
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Libraries
set(IDE_FOLDER "")
add_subdirectory(iozeug)
add_subdirectory(propertyguizeug)
add_subdirectory(propertyzeug)
add_subdirectory(signalzeug)
add_subdirectory(threadingzeug)
add_subdirectory(scriptzeug)

# Examples
add_subdirectory(examples)

# Tests
#add_subdirectory(tests)
