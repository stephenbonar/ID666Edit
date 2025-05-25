// SpcFile.cpp - Declares the SpcFile class.
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

bool SpcFile::Load()
{
    SpcFileStream file{ fileName };
    file.Open(Binary::FileMode::Read);

    if (!file.IsOpen())
        return false;

    file.Read(&header);
    
    if (file.HasBinaryTag())
        file.Read(&binaryTag);
    else
        file.Read(&textTag);

    if (file.HasExtendedTag())
    {
        extendedTagItems.clear();
        file.SeekExtendedTag();

        Binary::ChunkHeader tagHeader;
        file.Read(&tagHeader);
        std::string id = tagHeader.id.Value();
        std::string size = tagHeader.dataSize.ToString();
        size_t sizeRemaining = tagHeader.dataSize.Value();

        /*
        std::cout << FormatValue("Extended Tag ID", id) << std::endl;
        std::cout << FormatValue("Extended Tag Size", size) << std::endl;
        */

        while (sizeRemaining > 0)
        {
            ExtendedID666Item item;
            file.Read(&item);

            switch (item.type.Value())
            {
                case extendedTypeDataInHeader:
                    sizeRemaining -= item.Size();
                    extended
                    break;
                case extendedTypeString:
                {
                    size_t dataSize = item.data.Value();
                    sizeRemaining -= item.Size();
                    sizeRemaining -= dataSize;
                    Binary::StringField field{ item.data.Value() };
                    file.Read(&field);

                    if (dataSize % 4 != 0)
                    {
                        size_t paddingSize = 1;

                        while ((dataSize + paddingSize) % 4 != 0)
                            paddingSize++;

                        Binary::RawField padding{ paddingSize };
                        file.Read(&padding);
                        sizeRemaining -= paddingSize;
                    }

                    PrintExtendedItem(item, field);
                    break;
                }
                case extendedTypeInteger:
                {
                    sizeRemaining -= item.Size();
                    sizeRemaining -= item.data.Value();
                    Binary::UInt32Field field;
                    file.Read(&field);
                    PrintExtendedItem(item, field);
                    break;
                }
                default:
                    std::cerr << "Invalid extended item type. File may be corrupt.";
                    return;
            }
        }
    }
}

void SpcFile::InitializeExtendedFields()
{
    extendedSongName = nullptr;
    extendedGameName = nullptr;
    extendedArtistName = nullptr;
    extendedDumperName = nullptr;
    extendedDateDumped = nullptr;
    extendedEmulatorUsed = nullptr;
    extendedComments = nullptr;
    extendedOSTTitle = nullptr;
    extendedOSTDisk = nullptr;
    extendedOSTTrack = nullptr;
    extendedPublisherName = nullptr;
    extendedCopyrightYear = nullptr;
    extendedIntroLength = nullptr;
    extendedLoopLength = nullptr;
    extendedEndLength = nullptr;
    extendedFadeLength = nullptr;
    extendedMutedChannels = nullptr;
    extendedLoopTimes = nullptr;
    extendedPreamp = nullptr;
}