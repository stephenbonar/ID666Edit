// SpcHeader.h - Defines the SpcHeader struct.
//
// Copyright (C) 2025 Stephen Bonar
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "SpcHeader.h"

SpcHeader::SpcHeader()
{
    labeledFields.push_back({ "SPC Header ID", &ID });
    labeledFields.push_back({ "Separator", &separator });
    labeledFields.push_back({ "Contains Tag", &containsTag });
    labeledFields.push_back({ "Version Minor", &versionMinor });
    labeledFields.push_back({ "PC Register", &pcRegister });
    labeledFields.push_back({ "A Register", &aRegister });
    labeledFields.push_back({ "X Register", &xRegister });
    labeledFields.push_back({ "Y Register", &yRegister });
    labeledFields.push_back({ "PSW Register", &pswRegister });
    labeledFields.push_back({ "SP Register", &spRegister });
    labeledFields.push_back({ "Reserved", &reserved });
}
