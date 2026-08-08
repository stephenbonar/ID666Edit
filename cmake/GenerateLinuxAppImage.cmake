# GenerateLinuxAppImage.cmake - Builds an AppImage for ID666Edit on Linux.
#
# Expected -D variables:
#   APP_ID, APP_NAME, APP_EXECUTABLE, DESKTOP_FILE, ICONS_SOURCE_DIR,
#   APPDIR_ROOT, APPIMAGE_OUTPUT_DIR, LINUXDEPLOY_EXECUTABLE,
#   LINUXDEPLOY_GTK_PLUGIN

if(NOT DEFINED APP_ID OR APP_ID STREQUAL "")
    message(FATAL_ERROR "APP_ID is required")
endif()

if(NOT DEFINED APP_NAME OR APP_NAME STREQUAL "")
    message(FATAL_ERROR "APP_NAME is required")
endif()

if(NOT DEFINED APP_EXECUTABLE OR APP_EXECUTABLE STREQUAL "")
    message(FATAL_ERROR "APP_EXECUTABLE is required")
endif()

if(NOT EXISTS "${APP_EXECUTABLE}")
    message(FATAL_ERROR "APP_EXECUTABLE does not exist: ${APP_EXECUTABLE}")
endif()

if(NOT DEFINED DESKTOP_FILE OR DESKTOP_FILE STREQUAL "")
    message(FATAL_ERROR "DESKTOP_FILE is required")
endif()

if(NOT EXISTS "${DESKTOP_FILE}")
    message(FATAL_ERROR "DESKTOP_FILE does not exist: ${DESKTOP_FILE}")
endif()

if(NOT DEFINED ICONS_SOURCE_DIR OR ICONS_SOURCE_DIR STREQUAL "")
    message(FATAL_ERROR "ICONS_SOURCE_DIR is required")
endif()

if(NOT EXISTS "${ICONS_SOURCE_DIR}")
    message(FATAL_ERROR "ICONS_SOURCE_DIR does not exist: ${ICONS_SOURCE_DIR}")
endif()

if(NOT DEFINED APPDIR_ROOT OR APPDIR_ROOT STREQUAL "")
    message(FATAL_ERROR "APPDIR_ROOT is required")
endif()

if(NOT DEFINED APPIMAGE_OUTPUT_DIR OR APPIMAGE_OUTPUT_DIR STREQUAL "")
    message(FATAL_ERROR "APPIMAGE_OUTPUT_DIR is required")
endif()

set(DETECTED_ARCH "")
if(DEFINED CMAKE_HOST_SYSTEM_PROCESSOR AND
   NOT CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "")
    set(DETECTED_ARCH "${CMAKE_HOST_SYSTEM_PROCESSOR}")
elseif(DEFINED CMAKE_SYSTEM_PROCESSOR AND
       NOT CMAKE_SYSTEM_PROCESSOR STREQUAL "")
    set(DETECTED_ARCH "${CMAKE_SYSTEM_PROCESSOR}")
else()
    execute_process(
        COMMAND uname -m
        OUTPUT_VARIABLE DETECTED_ARCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
        RESULT_VARIABLE uname_result
    )
    if(NOT uname_result EQUAL 0)
        message(FATAL_ERROR "Could not detect host architecture")
    endif()
endif()

string(TOLOWER "${DETECTED_ARCH}" DETECTED_ARCH)
if(DETECTED_ARCH STREQUAL "amd64")
    set(DETECTED_ARCH "x86_64")
endif()

if(NOT DETECTED_ARCH MATCHES "^(x86_64|aarch64)$")
    message(FATAL_ERROR
        "Automatic AppImage generation supports x86_64 and aarch64 hosts. "
        "Detected: ${DETECTED_ARCH}")
endif()

set(APPDIR "${APPDIR_ROOT}/${APP_NAME}.AppDir")
set(TOOLS_DIR "${APPDIR_ROOT}/tools")
set(LINUXDEPLOY_BIN "${LINUXDEPLOY_EXECUTABLE}")
set(GTK_PLUGIN_BIN "${LINUXDEPLOY_GTK_PLUGIN}")

# Ensure output directories exist and remove previous AppDir state.
file(MAKE_DIRECTORY "${APPIMAGE_OUTPUT_DIR}")
file(MAKE_DIRECTORY "${TOOLS_DIR}")
file(REMOVE_RECURSE "${APPDIR}")

# Assemble a minimal AppDir filesystem.
file(MAKE_DIRECTORY "${APPDIR}/usr/bin")
file(MAKE_DIRECTORY "${APPDIR}/usr/share/applications")
file(MAKE_DIRECTORY "${APPDIR}/usr/share/pixmaps")

get_filename_component(APP_EXECUTABLE_BASENAME "${APP_EXECUTABLE}" NAME)
file(COPY "${APP_EXECUTABLE}" DESTINATION "${APPDIR}/usr/bin")
if(NOT APP_EXECUTABLE_BASENAME STREQUAL APP_NAME)
    file(RENAME "${APPDIR}/usr/bin/${APP_EXECUTABLE_BASENAME}"
                "${APPDIR}/usr/bin/${APP_NAME}")
endif()
file(COPY "${DESKTOP_FILE}" DESTINATION "${APPDIR}/usr/share/applications")
file(RENAME "${APPDIR}/usr/share/applications/${APP_ID}.desktop"
            "${APPDIR}/${APP_ID}.desktop")

foreach(icon_size IN ITEMS 16 20 24 32 40 48 64)
    set(SOURCE_ICON
        "${ICONS_SOURCE_DIR}/ID666Edit Icon ${icon_size}x${icon_size}.png")
    if(NOT EXISTS "${SOURCE_ICON}")
        message(FATAL_ERROR "Missing icon asset: ${SOURCE_ICON}")
    endif()

    set(TARGET_ICON_DIR
        "${APPDIR}/usr/share/icons/hicolor/${icon_size}x${icon_size}/apps")
    file(MAKE_DIRECTORY "${TARGET_ICON_DIR}")
    file(COPY "${SOURCE_ICON}" DESTINATION "${TARGET_ICON_DIR}")
    file(RENAME
        "${TARGET_ICON_DIR}/ID666Edit Icon ${icon_size}x${icon_size}.png"
        "${TARGET_ICON_DIR}/${APP_NAME}.png")
endforeach()

file(COPY "${ICONS_SOURCE_DIR}/ID666Edit Icon 64x64.png"
     DESTINATION "${APPDIR}/usr/share/pixmaps")
file(RENAME "${APPDIR}/usr/share/pixmaps/ID666Edit Icon 64x64.png"
            "${APPDIR}/usr/share/pixmaps/${APP_NAME}.png")
file(COPY "${APPDIR}/usr/share/pixmaps/${APP_NAME}.png" DESTINATION "${APPDIR}")

if(LINUXDEPLOY_BIN STREQUAL "")
    set(LINUXDEPLOY_BIN "${TOOLS_DIR}/linuxdeploy-${DETECTED_ARCH}.AppImage")
    if(NOT EXISTS "${LINUXDEPLOY_BIN}")
        message(STATUS "Downloading linuxdeploy...")
        file(DOWNLOAD
            "https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-${DETECTED_ARCH}.AppImage"
            "${LINUXDEPLOY_BIN}"
            STATUS download_status
            SHOW_PROGRESS)
        list(GET download_status 0 download_code)
        if(NOT download_code EQUAL 0)
            list(GET download_status 1 download_message)
            message(FATAL_ERROR
                "Failed to download linuxdeploy: ${download_message}")
        endif()
    endif()
endif()

if(GTK_PLUGIN_BIN STREQUAL "")
    set(GTK_PLUGIN_BIN "${TOOLS_DIR}/linuxdeploy-plugin-gtk.sh")
    if(NOT EXISTS "${GTK_PLUGIN_BIN}")
        message(STATUS "Downloading linuxdeploy GTK plugin...")
        file(DOWNLOAD
            "https://raw.githubusercontent.com/linuxdeploy/linuxdeploy-plugin-gtk/master/linuxdeploy-plugin-gtk.sh"
            "${GTK_PLUGIN_BIN}"
            STATUS download_status
            SHOW_PROGRESS)
        list(GET download_status 0 download_code)
        if(NOT download_code EQUAL 0)
            list(GET download_status 1 download_message)
            message(FATAL_ERROR
                "Failed to download GTK plugin: ${download_message}")
        endif()
    endif()
endif()

execute_process(COMMAND chmod +x "${LINUXDEPLOY_BIN}" "${GTK_PLUGIN_BIN}"
                RESULT_VARIABLE chmod_result)
if(NOT chmod_result EQUAL 0)
    message(FATAL_ERROR "Failed to set executable bit on linuxdeploy tools")
endif()

# Remove stale AppImage outputs before generating the next one.
file(GLOB stale_appimages "${APPIMAGE_OUTPUT_DIR}/*.AppImage")
if(stale_appimages)
    file(REMOVE ${stale_appimages})
endif()

set(APPIMAGE_OUTPUT_FILE
    "${APPIMAGE_OUTPUT_DIR}/${APP_NAME}-${DETECTED_ARCH}.AppImage")

execute_process(
    COMMAND ${CMAKE_COMMAND} -E env
            ARCH=${DETECTED_ARCH}
            APPIMAGE_EXTRACT_AND_RUN=1
            LDAI_OUTPUT=${APPIMAGE_OUTPUT_FILE}
            OUTPUT=${APPIMAGE_OUTPUT_FILE}
            "${LINUXDEPLOY_BIN}"
            --appdir "${APPDIR}"
            --desktop-file "${APPDIR}/${APP_ID}.desktop"
            --icon-file "${APPDIR}/${APP_NAME}.png"
            --plugin gtk
            --output appimage
    RESULT_VARIABLE linuxdeploy_result
)

if(NOT linuxdeploy_result EQUAL 0)
    message(FATAL_ERROR "linuxdeploy failed with code ${linuxdeploy_result}")
endif()

if(NOT EXISTS "${APPIMAGE_OUTPUT_FILE}")
    message(FATAL_ERROR
        "linuxdeploy completed but expected AppImage was not generated: "
        "${APPIMAGE_OUTPUT_FILE}")
endif()

message(STATUS "Generated AppImage: ${APPIMAGE_OUTPUT_FILE}")
