// SpcFile.h - Declares the SpcFile class.
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

#ifndef SPC_FILE_H
#define SPC_FILE_H

#include <string>
#include "RawFileStream.h"
#include "SpcHeader.h"
#include "ID666TextTag.h"
#include "ID666BinaryTag.h"

inline constexpr int headerContainsTag{ 26 }; 

class SpcFile
{
public:
    SpcFile(std::string fileName) : stream{ fileName }
    { }

    void Open();

    bool IsOpen() { return stream.IsOpen(); }

    void Read(Binary::DataField* field);

    void Read(Binary::DataStructure* structure);

    /*
    void Read(SpcHeader* header);

    void Read(ID666TextTag* tag);

    void Read(ID666BinaryTag* tag);

    void Read(Binary::ChunkHeader* header);
    */

    void SeekExtendedTag();

    bool HeaderContainsTag();

    bool HasBinaryTag();

    bool HasExtendedTag();
private:
    Binary::RawFileStream stream;
};

#endif