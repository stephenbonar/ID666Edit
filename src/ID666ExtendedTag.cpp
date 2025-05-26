// ID666ExtendedTag.h - Defines the ID666ExtendedTag class.
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

#include "ID666ExtendedTag.h"

std::vector<SpcField*> ID666ExtendedTag::SpcFields() const
{
    std::vector<SpcField*> spcFields;
    spcFields.push_back(songName.get());
    spcFields.push_back(gameName.get());
    spcFields.push_back(artistName.get());
    spcFields.push_back(dumperName.get());
    spcFields.push_back(dateDumped.get());
    spcFields.push_back(emulatorUsed.get());
    spcFields.push_back(comments.get());
    spcFields.push_back(ostTitle.get());
    spcFields.push_back(ostDisc.get());
    spcFields.push_back(ostTrack.get());
    spcFields.push_back(publisherName.get());
    spcFields.push_back(copyrightYear.get());
    spcFields.push_back(introLength.get());
    spcFields.push_back(loopLength.get());
    spcFields.push_back(endLength.get());
    spcFields.push_back(fadeLength.get());
    spcFields.push_back(mutedVoices.get());
    spcFields.push_back(loopTimes.get());
    spcFields.push_back(preampLevel.get());

    std::vector<SpcField*> nonNullFields;

    for (SpcField* field : spcFields)
    {
        if (field != nullptr)
            nonNullFields.push_back(field);
    }

    return nonNullFields;
}