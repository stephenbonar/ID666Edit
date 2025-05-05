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

std::vector<Binary::DataField*> SpcHeader::Fields()
{
    std::vector<Binary::DataField*> fields;
    fields.push_back(&ID);
    fields.push_back(&separator);
    fields.push_back(&containsTag);
    fields.push_back(&versionMinor);
    fields.push_back(&pcRegister);
    fields.push_back(&aRegister);
    fields.push_back(&xRegister);
    fields.push_back(&yRegister);
    fields.push_back(&pswRegister);
    fields.push_back(&spRegister);
    fields.push_back(&reserved);
    return fields;
}

size_t SpcHeader::Size() const
{
    size_t size{ 0 };
    size += ID.Size();
    size += separator.Size();
    size += containsTag.Size();
    size += versionMinor.Size();
    size += pcRegister.Size();
    size += aRegister.Size();
    size += xRegister.Size();
    size += yRegister.Size();
    size += pswRegister.Size();
    size += spRegister.Size();
    size += reserved.Size();
    return size;
}