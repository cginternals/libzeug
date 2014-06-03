
# Group source files in folders (e.g. for MSVC solutions)
# Example: source_group_by_path("${CMAKE_CURRENT_SOURCE_DIR}/src" 
#   "\\\\.h$|\\\\.hpp$|\\\\.cpp$|\\\\.c$|\\\\.ui$|\\\\.qrc$" "Source Files" ${sources})

macro(source_group_by_path PARENT_PATH REGEX GROUP)

    set(args ${ARGV})

    list(REMOVE_AT args 0)
    list(REMOVE_AT args 0)
    list(REMOVE_AT args 0)

    foreach(FILENAME ${args})

        get_filename_component(FILEPATH "${FILENAME}" REALPATH)
        file(RELATIVE_PATH FILEPATH ${PARENT_PATH} ${FILEPATH})
        get_filename_component(FILEPATH "${FILEPATH}" PATH)

        string(REPLACE "/" "\\" FILEPATH "${FILEPATH}")

        if(${FILENAME} MATCHES "${REGEX}")
            source_group("${GROUP}\\${FILEPATH}" FILES ${FILENAME})  
        endif()

    endforeach()

endmacro()


macro(list_extract OUTPUT REGEX)

    set(args ${ARGV})

    list(REMOVE_AT args 0)
    list(REMOVE_AT args 0)

    foreach(FILENAME ${args})

        if(${FILENAME} MATCHES "${REGEX}")
            list(APPEND ${OUTPUT} ${FILENAME})
        endif()

    endforeach()

endmacro()


include (GenerateExportHeader)

function(generate_library_export_header LIBNAME)

    string(TOUPPER ${LIBNAME}_API LIBRARY_EXPORT_MACRO)
    
    generate_export_header( ${LIBNAME}
        BASE_NAME ${LIBNAME}
        EXPORT_MACRO_NAME ${LIBRARY_EXPORT_MACRO}
        EXPORT_FILE_NAME ${LIBNAME}_api.h
        STATIC_DEFINE OPTION_BUILD_STATIC)
        
endfunction()
