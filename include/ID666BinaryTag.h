// ID666BinaryTag.h - Declares the ID666BinaryTag class.
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

#ifndef ID666_BINARY_TAG_H
#define ID666_BINARY_TAG_H

#include "SpcStruct.h"
#include "StringField.h"
#include "RawField.h"
#include "IntField.h"

struct ID666BinaryTag : public SpcStruct
{
    Binary::StringField songTitle{ 32 };
    Binary::StringField gameTitle{ 32 };
    Binary::StringField dumperName{ 16 };
    Binary::StringField comments{ 32 };
    Binary::UInt8Field dateDumpedDay;
    Binary::UInt8Field dateDumpedMonth;
    Binary::UInt16Field dateDumpedYear;
    Binary::RawField unused{ 7 };
    Binary::UInt24Field songLength;
    Binary::UInt32Field fadeLength;
    Binary::StringField songArtist{ 32 };
    Binary::UInt8Field defaultChannelDisables;
    Binary::UInt8Field emulatorUsed;
    Binary::RawField reserved{ 46 };

    ID666BinaryTag();

    std::vector<std::pair<std::string, Binary::DataField*>> 
        LabeledFields() const override { return labeledFields; }
private:
    std::vector<std::pair<std::string, Binary::DataField*>> labeledFields;
};

#endif