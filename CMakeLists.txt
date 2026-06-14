# CMakeLists.txt - Builds the ID666Edit project.
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

cmake_minimum_required(VERSION 3.10.0)

# On Windows, force a consistent static CRT model for all targets,
# including C-based third-party deps (png/zlib/expat) and C++ code.
# CMP0091/CMAKE_MSVC_RUNTIME_LIBRARY must be set before project().
if (WIN32 AND POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

project(ID666Edit VERSION 1.0.0 LANGUAGES C CXX)

# Fallback for older CMake versions that don't support CMP0091.
if (MSVC AND NOT POLICY CMP0091)
    foreach(_cfg DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
        string(TOUPPER "${_cfg}" _cfg_upper)
        if (_cfg STREQUAL "DEBUG")
            set(CMAKE_C_FLAGS_${_cfg_upper} "${CMAKE_C_FLAGS_${_cfg_upper}} /MTd")
            set(CMAKE_CXX_FLAGS_${_cfg_upper} "${CMAKE_CXX_FLAGS_${_cfg_upper}} /MTd")
        else()
            set(CMAKE_C_FLAGS_${_cfg_upper} "${CMAKE_C_FLAGS_${_cfg_upper}} /MT")
            set(CMAKE_CXX_FLAGS_${_cfg_upper} "${CMAKE_CXX_FLAGS_${_cfg_upper}} /MT")
        endif()
    endforeach()
endif()

# Specify the C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Option to enable/disable building the GUI (wxWidgets-based) target.
# Default ON so GUI builds unless the user passes -DBUILD_GUI=OFF.
option(BUILD_GUI "Build the GUI application (requires wxWidgets)" ON)

add_subdirectory(lib/LibCppSpc)

add_subdirectory(lib/LibCppCmdLine)

if(BUILD_GUI)
    set(wxBUILD_SHARED OFF)
    set(wxBUILD_USE_STATIC_RUNTIME ON)
    add_subdirectory(lib/wxWidgets)
endif()

add_subdirectory(src)
