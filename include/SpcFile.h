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
#include <memory>
#include <vector>
#include <map>
#include "SpcHeader.h"
#include "ID666BinaryTag.h"
#include "ID666TextTag.h"
#include "ID666ExtendedTag.h"
#include "ExtendedID666Item.h"
#include "SpcFileStream.h"

class SpcFile
{
public:
    SpcFile(std::string fileName) : 
        fileName{ fileName }, 
        hasLoaded{ false }, 
        hasBinaryTag{ false },
        hasExtendedTag{ false },
        headerContainsTag{ false }
    {}

    std::string FileName() const { return fileName; }

    bool HasLoaded() const { return hasLoaded; }

    bool HasBinaryTag() const { return hasBinaryTag; }

    bool HasExtendedTag() const { return hasExtendedTag; }

    bool HeaderContainsTag() const { return headerContainsTag; }

    SpcHeader Header() const { return header; }

    ID666BinaryTag BinaryTag() const { return binaryTag; }

    ID666TextTag TextTag() const { return textTag; }

    ID666ExtendedTag ExtendedTag() const { return extendedTag; }

    SpcTextField SongTitle() const;

    SpcTextField GameTitle() const;

    SpcTextField DumperName() const;

    SpcTextField Comments() const;

    SpcDateField DateDumped() const;

    SpcNumericField SongLength() const;

    SpcNumericField FadeLength() const;

    SpcTextField SongArtist() const;

    SpcNumericField DefaultChannelDisables() const;

    SpcEmulatorField EmulatorUsed() const;

    SpcTextField OstTitle() const;

    SpcNumericField OstDisc() const;

    SpcTrackField OstTrack() const;

    SpcTextField PublisherName() const;

    SpcNumericField CopyrightYear() const;

    SpcNumericField IntroLength() const;

    SpcNumericField LoopLength() const;

    SpcNumericField EndLength() const;

    //SpcNumericField FadeLength() const;

    SpcBinaryField MutedVoices() const;

    SpcNumericField LoopTimes() const;

    SpcNumericField PreampLevel() const;

    bool Load();

    bool Save();
private:
    std::string fileName;
    bool hasLoaded;
    bool hasBinaryTag;
    bool hasExtendedTag;
    bool headerContainsTag;
    SpcHeader header;
    ID666BinaryTag binaryTag;
    ID666TextTag textTag;
    ID666ExtendedTag extendedTag;

    //void InitExtendedFields();

    void LoadHeaderField(ExtendedID666Item& item);

    void LoadTextField(ExtendedID666Item& item, SpcFileStream& stream);

    void LoadNumericField(ExtendedID666Item&item, SpcFileStream& stream);
};

template<typename T>
std::shared_ptr<T> InitField(int extendedID, size_t size)
{
    std::string label = "<Unknown Field>";
    constexpr uintmax_t offset{ extendedTagOffset };

    if (extendedFieldLabels.find(extendedID) != extendedFieldLabels.end())
        label = extendedFieldLabels.at(extendedID);

    return std::make_shared<T>(label, offset, size);
}

#endif