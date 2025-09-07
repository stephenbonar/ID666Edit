# CMakeLists.txt - Builds the ID666Edit application.
#
# Copyright (C) 2025 Stephen Bonar
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

set(INCLUDES 
    ${PROJECT_SOURCE_DIR}/include)

add_executable(id666editc main.cpp Program.cpp)

add_executable(ID666Edit ID666Edit.cpp MainWindow.cpp FileNameToTagWindow.cpp)

target_include_directories(id666editc PUBLIC ${INCLUDES})

target_include_directories(ID666Edit PUBLIC ${INCLUDES})

target_link_libraries(id666editc LibCppCmdLine LibCppSpc)

target_link_libraries(ID666Edit wx::net wx::core wx::base LibCppSpc)