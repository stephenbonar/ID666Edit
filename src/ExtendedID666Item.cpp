// ExtendedID666Item.h - Defines the ExtendedID666Item class.
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

#include "ExtendedID666Item.h"

const std::map<int, std::string> extendedFieldLabels
{
    { extendedSongNameID, "Song Title" },
    { extendedGameNameID, "Game Title" },
    { extendedArtistNameID, "Song Artist" }, 
    { extendedDumperNameID, "Dumper Name" },
    { extendedDateDumpedID, "Date Dumped" },
    { extendedEmulatorUsedID, "Emulator Used" },
    { extendedCommentsID, "Comments" },
    { extendedOSTTitleID, "OST Title" },
    { extendedOSTDiscID, "OST Disc" },
    { extendedOSTTrackID, "OST Track" },
    { extendedPublisherNameID, "Publisher Name" },
    { extendedCopyrightYearID, "Copyright Year" },
    { extendedIntroLengthID, "Intro Length" },
    { extendedLoopLengthID, "Loop Length" },
    { extendedEndLengthID, "End Length" },
    { extendedFadeLengthID, "Fade Length" },
    { extendedMutedVoicesID, "Muted Voices" },
    { extendedLoopTimesID, "Loop Times" },
    { extendedPreampLevelID, "Preamp Level" }
};

ExtendedID666Item::ExtendedID666Item()
{
    spcFields.push_back(&id);
    spcFields.push_back(&type);
    spcFields.push_back(&data);
}