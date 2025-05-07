// SpcFile.h - Defines the SpcFile class.
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

#include "SpcFile.h"

void SpcFile::Open()
{
    stream.Open(Binary::FileMode::Read);
}

bool SpcFile::HeaderContainsTag()
{
    SpcHeader header;
    Read(&header);

    if (header.containsTag.Value() == headerContainsTag)
        return true;
    
    return false;
}

bool SpcFile::HasBinaryTag()
{
    uintmax_t previousPosition = stream.Position();
    stream.SetPosition(0x9E);
    Binary::UInt8Field nextByte;
    bool hasBinaryValue = false;

    for (int i = 0x9E; i < 0xB1; i++)
    {
        stream.Read(&nextByte);
        bool isAsciiNum = nextByte.Value() >= 0x30 && nextByte.Value() <= 0x39;
        bool isZero = nextByte.Value() == 0x0;
        bool isDateSlash = nextByte.Value() == 0x2F;

        if (!isAsciiNum && !isZero && !isDateSlash)
        {
            stream.SetPosition(previousPosition);
            return true;
        }
    }

    stream.SetPosition(previousPosition);
    return false;
}

void SpcFile::Read(SpcHeader* header)
{
    uintmax_t previousPosition = stream.Position();
    stream.SetPosition(0);
    stream.Read(header);
    stream.SetPosition(previousPosition);
}

void SpcFile::Read(ID666TextTag* tag)
{
    uintmax_t previousPosition = stream.Position();
    stream.SetPosition(0x2E);
    stream.Read(tag);
    stream.SetPosition(previousPosition);
}

void SpcFile::Read(ID666BinaryTag* tag)
{
    uintmax_t previousPosition = stream.Position();
    stream.SetPosition(0x2E);
    stream.Read(tag);
    stream.SetPosition(previousPosition);
}