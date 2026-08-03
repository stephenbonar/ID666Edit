# CMakeLists.txt - Builds the ID666Edit application.
#
# Copyright (C) 2026 Stephen Bonar
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http ://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Configure Version.h to pull in project version and other metadata from
# CMake so the program can display it in the About dialog and other places.
configure_file(${PROJECT_SOURCE_DIR}/include/Version.h.in
               ${CMAKE_BINARY_DIR}/Version.h
               @ONLY)

set(INCLUDES 
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR})

# Add Windows specific resource information into the executable so the program
# can display version information, other metadata, and the icon.
if(WIN32)
    function(add_windows_resource_metadata target file_description)
        set(WINDOWS_FILE_DESCRIPTION "${file_description}")
        set(WINDOWS_INTERNAL_NAME "${target}")
        set(WINDOWS_ORIGINAL_FILENAME "${target}.exe")

        configure_file(
            ${PROJECT_SOURCE_DIR}/resources/windows/ID666Edit.rc.in
            ${CMAKE_BINARY_DIR}/${target}.rc
            @ONLY
        )

        target_sources(${target} PRIVATE
            ${CMAKE_BINARY_DIR}/${target}.rc
        )

        if(MSVC)
            target_link_options(${target} PRIVATE /MANIFEST:NO)
        endif()
    endfunction()
endif()

# Define the main executable target for the command line version so we can
# build the command line executable.
add_executable(id666editc main.cpp Program.cpp)

# Configure the include directories so the compiler can find the header files.
target_include_directories(id666editc PUBLIC ${INCLUDES})

# Link the command line application against the LibCppCmdLine and LibCppSpc 
# libraries so it can use those APIs.
target_link_libraries(id666editc LibCppCmdLine LibCppSpc)

if(WIN32)
    add_windows_resource_metadata(id666editc "ID666Edit CLI")
endif()

# Define the GUI executable target if the user has requested to build the GUI
# version of the app.
if(BUILD_GUI)
    if (APPLE)
        # On macOS, we need to build the GUI version as a bundle so it can be
        # run as a proper macOS application, including proper icon and metadata.
        add_executable(ID666Edit MACOSX_BUNDLE
                       ID666Edit.cpp
                       Common.cpp
                       MainWindow.cpp
                       FileNameToTagDialog.cpp
                       PropertiesDialog.cpp
                       TagToFileNameWindow.cpp
                       IncrementTrackWindow.cpp)
    elseif (WIN32)
        # On Windows, we need to build the GUI version as a WIN32 executable
        # so it can be run as a proper Windows application, including proper 
        # icon and metadata.
        add_executable(ID666Edit WIN32
                       ID666Edit.cpp 
                       Common.cpp
                       MainWindow.cpp 
                       FileNameToTagDialog.cpp 
                       PropertiesDialog.cpp
                       TagToFileNameWindow.cpp
                       IncrementTrackWindow.cpp)

        # Suppress warnings about unsafe CRT functions from wxWidgets.
        target_compile_definitions(ID666Edit PRIVATE _CRT_SECURE_NO_WARNINGS)
        target_compile_options(ID666Edit PRIVATE
            /wd4996   # unsafe CRT warnings from wxWidgets
            /wd4251   # dll-interface warnings from wxWidgets
)
    else()
        add_executable(ID666Edit
                       ID666Edit.cpp
                       Common.cpp
                       MainWindow.cpp 
                       FileNameToTagDialog.cpp
                       PropertiesDialog.cpp
                       TagToFileNameWindow.cpp
                       IncrementTrackWindow.cpp)
    endif()

    # Configure the include directories so the compiler can find the header 
    # files.
    target_include_directories(ID666Edit PUBLIC ${INCLUDES})

    # Link the GUI application against the wxWidgets libraries and the 
    # LibCppSpc libraries so it can use those APIs.
    target_link_libraries(ID666Edit wx::net wx::core wx::base LibCppSpc)

    # Configure the macOS bundle with the proper icon and metadata if we are
    # building on macOS.
    if(APPLE)
        find_program(ICONUTIL_EXECUTABLE iconutil REQUIRED)
        find_program(SIPS_EXECUTABLE sips REQUIRED)

        set(MACOS_ICONSET_DIR ${CMAKE_CURRENT_BINARY_DIR}/ID666Edit.iconset)
        set(MACOS_ICON_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ID666Edit.icns)

        add_custom_command(
            OUTPUT ${MACOS_ICON_OUTPUT}
            COMMAND ${CMAKE_COMMAND}
                    -DICONUTIL_EXECUTABLE=${ICONUTIL_EXECUTABLE}
                    -DSIPS_EXECUTABLE=${SIPS_EXECUTABLE}
                    -DICONSET_DIR=${MACOS_ICONSET_DIR}
                    -DOUTPUT_ICNS=${MACOS_ICON_OUTPUT}
                    -DICON_16=${PROJECT_SOURCE_DIR}/resources/icons/ID666Edit\ Icon\ 16x16.png
                    -DICON_32=${PROJECT_SOURCE_DIR}/resources/icons/ID666Edit\ Icon\ 32x32.png
                    -DICON_64=${PROJECT_SOURCE_DIR}/resources/icons/ID666Edit\ Icon\ 64x64.png
                    -P ${PROJECT_SOURCE_DIR}/cmake/GenerateMacOSIcon.cmake
            DEPENDS
                    ${PROJECT_SOURCE_DIR}/resources/icons/ID666Edit\ Icon\ 16x16.png
                    ${PROJECT_SOURCE_DIR}/resources/icons/ID666Edit\ Icon\ 32x32.png
                    ${PROJECT_SOURCE_DIR}/resources/icons/ID666Edit\ Icon\ 64x64.png
                    ${PROJECT_SOURCE_DIR}/cmake/GenerateMacOSIcon.cmake
            VERBATIM
        )

        set_source_files_properties(${MACOS_ICON_OUTPUT}
            PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
        target_sources(ID666Edit PRIVATE ${MACOS_ICON_OUTPUT})
        set_target_properties(ID666Edit PROPERTIES
            MACOSX_BUNDLE_BUNDLE_NAME ID666Edit
            MACOSX_BUNDLE_GUI_IDENTIFIER com.stephenbonar.id666edit
            MACOSX_BUNDLE_INFO_STRING "ID666Edit SPC Tag Editor"
            MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
            MACOSX_BUNDLE_LONG_VERSION_STRING "${PROJECT_VERSION} ${PROGRAM_RELEASE}"
            MACOSX_BUNDLE_COPYRIGHT "${PROGRAM_COPYRIGHT}"
            MACOSX_BUNDLE_ICON_FILE ID666Edit.icns)
    endif()

    if(WIN32)
        add_windows_resource_metadata(ID666Edit "ID666Edit SPC Tag Editor")
    endif()
endif()
