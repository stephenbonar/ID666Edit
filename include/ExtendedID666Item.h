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

/// @brief Represents an item in the extended ID666 tag.
///
/// The extended ID666 tag is a RIFF chunk that contains multiple sub-chunks
/// representing items in the tag. This struct represents those sub-chunks.
struct ExtendedID666Item : public SpcStruct
{
    /// @brief The ID of the item, which determines which metadata field it is.
    SpcNumericField id{ "Extended Item ID", 0x10200, 1 };

    /// @brief Determines the data type: data in header, string, or integer.
    SpcNumericField type{ "Extented Item Type", 0x10200, 1};

    /// @brief Either represents the value if type 0, or the size of value.
    SpcNumericField data{ "Extended Item Data", 0x10200, 2};

    /// @brief Default constructor; initalizes the labeled fields list.
    ///
    /// While this is a standard struct with public fields, it is also an 
    /// SpcStruct, which maintains an internal vector of labeled pointers to
    /// each public field accessible via the SpcFields() method. The 
    /// constructor initializes this internal vector.
    ExtendedID666Item();

    /// @brief Gets list of pointers to this struct's fields.
    ///
    /// This method will be called by the ToString() method to output each
    /// field as a formatted string on its own line of the format,
    ///
    /// label: value
    ///
    /// This method is also called by the Fields() method to get a pointer to
    /// each field so SpcFileStream can read this struct from and write it to
    /// an SPC file in a cross platform way, preserving the order, size, and
    /// endianness of each field no matter which architecture the program runs
    /// on.
    std::vector<SpcField*> SpcFields() const override { return spcFields; }
private:
    std::vector<SpcField*> spcFields;
};

#endif