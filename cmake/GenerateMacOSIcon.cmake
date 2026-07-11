if(NOT DEFINED ICONUTIL_EXECUTABLE OR NOT DEFINED SIPS_EXECUTABLE)
    message(FATAL_ERROR "Missing icon generation tools")
endif()

if(NOT DEFINED ICONSET_DIR OR NOT DEFINED OUTPUT_ICNS)
    message(FATAL_ERROR "Missing icon output paths")
endif()

if(NOT DEFINED ICON_16 OR NOT DEFINED ICON_32 OR NOT DEFINED ICON_64)
    message(FATAL_ERROR "Missing source icon files")
endif()

file(REMOVE_RECURSE "${ICONSET_DIR}")
file(MAKE_DIRECTORY "${ICONSET_DIR}")

function(generate_icon input_file size output_name)
    execute_process(
        COMMAND "${SIPS_EXECUTABLE}" -z ${size} ${size} "${input_file}"
                --out "${ICONSET_DIR}/${output_name}"
        RESULT_VARIABLE result
        OUTPUT_QUIET
        ERROR_VARIABLE error_text
    )

    if(NOT result EQUAL 0)
        message(FATAL_ERROR "Failed to generate ${output_name}: ${error_text}")
    endif()
endfunction()

generate_icon("${ICON_16}" 16 "icon_16x16.png")
generate_icon("${ICON_32}" 32 "icon_16x16@2x.png")
generate_icon("${ICON_32}" 32 "icon_32x32.png")
generate_icon("${ICON_64}" 64 "icon_32x32@2x.png")
generate_icon("${ICON_64}" 128 "icon_128x128.png")
generate_icon("${ICON_64}" 256 "icon_128x128@2x.png")
generate_icon("${ICON_64}" 256 "icon_256x256.png")
generate_icon("${ICON_64}" 512 "icon_256x256@2x.png")
generate_icon("${ICON_64}" 512 "icon_512x512.png")
generate_icon("${ICON_64}" 1024 "icon_512x512@2x.png")

execute_process(
    COMMAND "${ICONUTIL_EXECUTABLE}" -c icns "${ICONSET_DIR}" -o "${OUTPUT_ICNS}"
    RESULT_VARIABLE result
    OUTPUT_QUIET
    ERROR_VARIABLE error_text
)

if(NOT result EQUAL 0)
    message(FATAL_ERROR "Failed to generate macOS app icon: ${error_text}")
endif()