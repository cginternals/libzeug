# Create output directory
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/packages)

# Target 'pack'
add_custom_target(packzeug)
set_target_properties(packzeug PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)

# Packages
include(pack-libzeug.cmake)
