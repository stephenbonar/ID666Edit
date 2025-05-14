// SpcDateField.cpp - Defines the SpcDateField class.
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

#include "SpcDateField.h"

bool SpcDateField::IsText() const
{
    for (int i = 0; i < size; i++)
    {
        bool isAsciiNum = data[i] >= 0x30 && data[i] <= 0x39;
        bool isZero = data[i] == 0x0;
        bool isDateSlash = data[i] == 0x2F;

        if (!isAsciiNum && !isZero && !isDateSlash)
            return false;
    }

    return true;
}

bool SpcDateField::HasUnusedArea() const
{
    constexpr int unusedAreaIndex{ 4 };

    for (int i = unusedAreaIndex; i < size; i++)
    {
        if (data[i] != 0)
            return false;
    }

    return true;
}

std::string SpcDateField::ToString() const
{
    if (IsText())
        return Binary::RawField::ToString(Binary::StringFormat::Terminated);

    Binary::UInt8Field day{ Binary::FieldEndianness::Little };
    Binary::UInt8Field month{ Binary::FieldEndianness::Little };
    Binary::UInt16Field year{ Binary::FieldEndianness::Little };

    day.Data()[0] = data[0];
    month.Data()[0] = data[1];
    year.Data()[0] = data[2];
    year.Data()[1] = data[3];

    std::stringstream stream;
    stream << month.ToString() << '/' << day.ToString() << '/' 
           << year.ToString();
    return stream.str();
}