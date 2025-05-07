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

std::vector<Binary::DataField*> ID666TextTag::Fields()
{
    std::vector<Binary::DataField*> fields;
    fields.push_back(&songTitle);
    fields.push_back(&gameTitle);
    fields.push_back(&dumperName);
    fields.push_back(&comments);
    fields.push_back(&dateDumped);
    fields.push_back(&songLength);
    fields.push_back(&fadeLength);
    fields.push_back(&songArtist);
    fields.push_back(&defaultChannelDisables);
    fields.push_back(&emulatorUsed);
    fields.push_back(&reserved);
    return fields;
}

size_t ID666TextTag::Size() const
{
    size_t size{ 0 };
    size += songTitle.Size();
    size += gameTitle.Size();
    size += dumperName.Size();
    size += comments.Size();
    size += dateDumped.Size();
    size += songLength.Size();
    size += fadeLength.Size();
    size += songArtist.Size();
    size += defaultChannelDisables.Size();
    size += emulatorUsed.Size();
    size += reserved.Size();
    return size;
}