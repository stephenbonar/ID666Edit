// ID666TextTag.h - Defines the ID666TextTag class.
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

#include "ID666TextTag.h"

ID666TextTag::ID666TextTag()
{
    labeledFields.push_back({ "Song Title", &songTitle });
    labeledFields.push_back({ "Game Title", &gameTitle });
    labeledFields.push_back({ "Dumper", &dumperName });
    labeledFields.push_back({ "Comments", &comments });
    labeledFields.push_back({ "Date Dumped", &dateDumped });
    labeledFields.push_back({ "Song Length (Sec)", &songLength });
    labeledFields.push_back({ "Fade Length (MS)", &fadeLength });
    labeledFields.push_back({ "Song Artist", &songArtist });
    labeledFields.push_back({ "Default Channel Disables", 
        &defaultChannelDisables });
    labeledFields.push_back({ "Emulator Used", &emulatorUsed });
    labeledFields.push_back({ "Reserved", &reserved });
}