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
#include "SpcHeader.h"
#include "ID666BinaryTag.h"
#include "ID666TextTag.h"
#include "ExtendedID666Item.h"
#include "SpcFileStream.h"

class SpcFile
{
public:
    SpcFile(std::string fileName) : fileName{ fileName }
    {}

    std::string FileName() const;

    SpcHeader Header() const;

    ID666BinaryTag BinaryTag() const;

    ID666TextTag TextTag() const;

    SpcTextField SongTitle() const;

    SpcTextField GameTitle() const;

    SpcTextField SongArtist() const;

    SpcTextField DumperName() const;

    bool Load();

    bool Save();
private:
    std::string fileName;
    SpcHeader header;
    ID666BinaryTag binaryTag;
    ID666TextTag textTag;
    std::unique_ptr<SpcTextField> extendedSongName;
    std::unique_ptr<SpcTextField> extendedGameName;
    std::unique_ptr<SpcTextField> extendedArtistName;
    std::unique_ptr<SpcTextField> extendedDumperName;
    std::unique_ptr<SpcNumericField> extendedDateDumped;
    std::unique_ptr<SpcNumericField> extendedEmulatorUsed;
    std::unique_ptr<SpcTextField> extendedComments;
    std::unique_ptr<SpcTextField> extendedOSTTitle;
    std::unique_ptr<SpcNumericField> extendedOSTDisk;
    std::unique_ptr<SpcNumericField> extendedOSTTrack;
    std::unique_ptr<SpcTextField> extendedPublisherName;
    std::unique_ptr<SpcNumericField> extendedCopyrightYear;
    std::unique_ptr<SpcNumericField> extendedIntroLength;
    std::unique_ptr<SpcNumericField> extendedLoopLength;
    std::unique_ptr<SpcNumericField> extendedEndLength;
    std::unique_ptr<SpcNumericField> extendedFadeLength;
    std::unique_ptr<SpcNumericField> extendedMutedChannels;
    std::unique_ptr<SpcNumericField> extendedLoopTimes;
    std::unique_ptr<SpcNumericField> extendedPreamp;

    void InitializeExtendedFields();
};

#endif