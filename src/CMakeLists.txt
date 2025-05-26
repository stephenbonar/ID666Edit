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

set(SOURCES 
    main.cpp
    Program.cpp
    SpcHeader.cpp
    ID666BinaryTag.cpp
    ID666TextTag.cpp
    ID666ExtendedTag.cpp
    SpcFileStream.cpp
    SpcFormat.cpp
    SpcStruct.cpp
    SpcHeader.cpp
    ExtendedID666Item.cpp
    SpcDateField.cpp
    SpcNumericField.cpp
    SpcEmulatorField.cpp
    SpcFile.cpp
    SpcTrackField.cpp)

set(INCLUDES 
    ${PROJECT_SOURCE_DIR}/include)

set(LIBRARIES LibCppBinary LibCppCmdLine)

add_executable(id666edit ${SOURCES})

target_include_directories(id666edit PUBLIC ${INCLUDES})

target_link_libraries(id666edit ${LIBRARIES})