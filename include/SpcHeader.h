// SpcHeader.h - Declares the SpcHeader struct.
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

#ifndef SPC_HEADER_H
#define SPC_HEADER_H

#include <vector>
#include "StringField.h"
#include "RawField.h"
#include "IntField.h"
#include "SpcStruct.h"

struct SpcHeader : public SpcStruct
{
    Binary::StringField ID{ 33 };
    Binary::RawField separator{ 2 };
    Binary::UInt8Field containsTag;
    Binary::UInt8Field versionMinor;
    Binary::RawField pcRegister{ 2 };
    Binary::RawField aRegister{ 1 };
    Binary::RawField xRegister{ 1 };
    Binary::RawField yRegister{ 1 };
    Binary::RawField pswRegister{ 1 };
    Binary::RawField spRegister{ 1 };
    Binary::RawField reserved{ 2 };

    SpcHeader();

    std::vector<std::pair<std::string, Binary::DataField*>> 
        LabeledFields() const override { return labeledFields; }
private:
    std::vector<std::pair<std::string, Binary::DataField*>> labeledFields;
};

#endif