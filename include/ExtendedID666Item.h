// ExtendedID666Item.h - Declares the ExtendedID666Item class.
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

#include "SpcStruct.h"
#include "SpcNumericField.h"

#ifndef EXTENDED_ID666_ITEM_H
#define EXTENDED_ID666_ITEM_H

inline constexpr uint8_t extendedSongNameID{ 0x1 };
inline constexpr uint8_t extendedGameNameID{ 0x2 };
inline constexpr uint8_t extendedArtistNameID{ 0x3 };
inline constexpr uint8_t extendedDumperNameID{ 0x4 };
inline constexpr uint8_t extendedDateDumpedID{ 0x5 };
inline constexpr uint8_t extendedEmulatorUsedID{ 0x6 };
inline constexpr uint8_t extendedCommentsID{ 0x7 };
inline constexpr uint8_t extendedOSTTitleID{ 0x10 };
inline constexpr uint8_t extendedOSTDiskID{ 0x11 };
inline constexpr uint8_t extendedOSTTrackID{ 0x12 };
inline constexpr uint8_t extendedPublisherNameID{ 0x13 };
inline constexpr uint8_t extendedCopyrightYearID{ 0x14 };
inline constexpr uint8_t extendedIntroLengthID{ 0x30 };
inline constexpr uint8_t extendedLoopLengthID{ 0x31 };
inline constexpr uint8_t extendedEndLengthID{ 0x32 };
inline constexpr uint8_t extendedFadeLengthID{ 0x33 };
inline constexpr uint8_t extendedMutedVoicesID{ 0x34 };
inline constexpr uint8_t extendedLoopTimesID{ 0x35 };
inline constexpr uint8_t extendedPreampLevelID{ 0x36 };
inline constexpr uint8_t extendedTypeDataInHeader{ 0 };
inline constexpr uint8_t extendedTypeString{ 1 };
inline constexpr uint8_t extendedTypeInteger{ 4 };

struct ExtendedID666Item : public SpcStruct
{
    SpcNumericField id{ "Extended Item ID", 0x10200, 1 };
    SpcNumericField type{ "Extented Item Type", 0x10200, 1};
    SpcNumericField data{ "Extended Item Data", 0x10200, 2};

    ExtendedID666Item();

    std::vector<SpcField*> SpcFields() const override { return spcFields; }
private:
    std::vector<SpcField*> spcFields;
};

#endif