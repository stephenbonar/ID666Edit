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

configure_file(${PROJECT_SOURCE_DIR}/include/Version.h.in
               ${CMAKE_BINARY_DIR}/Version.h
               @ONLY)

set(INCLUDES 
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR})

if(WIN32)
    #set(WINDOWS_COMPANY_NAME "Stephen Bonar")
    #set(WINDOWS_COPYRIGHT "Copyright (C) 2026 Stephen Bonar")
    #set(WINDOWS_PRODUCT_NAME "ID666Edit")

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

add_executable(id666editc main.cpp Program.cpp)

if(WIN32)
    add_windows_resource_metadata(id666editc "ID666Edit CLI")
endif()

if(BUILD_GUI)
    if (WIN32)
        add_executable(ID666Edit WIN32
                       ID666Edit.cpp 
                       MainWindow.cpp 
                       FileNameToTagWindow.cpp 
                       TagToFileNameWindow.cpp
                       IncrementTrackWindow.cpp)
    else()
        add_executable(ID666Edit
                       ID666Edit.cpp 
                       MainWindow.cpp 
                       FileNameToTagWindow.cpp 
                       TagToFileNameWindow.cpp
                       IncrementTrackWindow.cpp)
    endif()

    target_include_directories(ID666Edit PUBLIC ${INCLUDES})

    target_link_libraries(ID666Edit wx::net wx::core wx::base LibCppSpc)

    if(WIN32)
        add_windows_resource_metadata(ID666Edit "ID666Edit SPC Tag Editor")
    endif()
endif()

target_include_directories(id666editc PUBLIC ${INCLUDES})

target_link_libraries(id666editc LibCppCmdLine LibCppSpc)