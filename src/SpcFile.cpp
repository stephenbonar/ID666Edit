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

SpcTextField SpcFile::SongTitle() const
{
    if (extendedTag.songName != nullptr)
        return *extendedTag.songName;

    if (hasBinaryTag)
        return binaryTag.songTitle;
    else
        return textTag.songTitle;
}

SpcTextField SpcFile::GameTitle() const
{
    if (extendedTag.gameName != nullptr)
        return *extendedTag.gameName;

    if (hasBinaryTag)
        return binaryTag.gameTitle;
    else
        return textTag.gameTitle;
}

SpcTextField SpcFile::DumperName() const
{
    if (extendedTag.dumperName != nullptr)
        return *extendedTag.dumperName;

    if (hasBinaryTag)
        return binaryTag.dumperName;
    else
        return textTag.dumperName;
}

SpcTextField SpcFile::Comments() const
{
    if (extendedTag.comments != nullptr)
        return *extendedTag.comments;

    if (hasBinaryTag)
        return binaryTag.comments;
    else
        return textTag.comments;
}

SpcDateField SpcFile::DateDumped() const
{
    if (extendedTag.dateDumped != nullptr)
        return *extendedTag.dateDumped;

    if (hasBinaryTag)
        return binaryTag.dateDumped;
    else
        return textTag.dateDumped;
}

SpcNumericField SpcFile::SongLength() const
{
    if (hasBinaryTag)
        return binaryTag.songLength;
    else
        return textTag.songLength;
}

SpcNumericField SpcFile::FadeLength() const
{
    if (hasBinaryTag)
        return binaryTag.fadeLength;
    else
        return textTag.fadeLength;
}

SpcTextField SpcFile::SongArtist() const
{
    if (extendedTag.artistName != nullptr)
        return *extendedTag.artistName;

    if (hasBinaryTag)
        return binaryTag.songArtist;
    else
        return textTag.songArtist;
}

SpcNumericField SpcFile::DefaultChannelDisables() const
{
    if (hasBinaryTag)
        return binaryTag.defaultChannelDisables;
    else
        return textTag.defaultChannelDisables;
}

SpcEmulatorField SpcFile::EmulatorUsed() const
{
    if (extendedTag.emulatorUsed != nullptr)
        return *extendedTag.emulatorUsed;
    
    if (hasBinaryTag)
        return binaryTag.emulatorUsed;
    else
        return textTag.emulatorUsed;
}

SpcTextField SpcFile::OstTitle() const
{
    if (extendedTag.ostTitle != nullptr)
        return *extendedTag.ostTitle;
    else
        return *InitField<SpcTextField>(extendedOSTTitleID, 1);
}

SpcNumericField SpcFile::OstDisc() const
{
    if (extendedTag.ostDisc != nullptr)
        return *extendedTag.ostDisc;
    else
        return *InitField<SpcNumericField>(extendedOSTDiscID, 4);
}

SpcTrackField SpcFile::OstTrack() const
{
    if (extendedTag.ostTrack != nullptr)
        return *extendedTag.ostTrack;
    else
        return *InitField<SpcTrackField>(extendedOSTTrackID, 1);
}

SpcTextField SpcFile::PublisherName() const
{
    if (extendedTag.publisherName != nullptr)
        return *extendedTag.publisherName;
    else
        return *InitField<SpcTextField>(extendedPublisherNameID, 1);
}

SpcNumericField SpcFile::CopyrightYear() const
{
    if (extendedTag.copyrightYear != nullptr)
        return *extendedTag.copyrightYear;
    else
        return *InitField<SpcNumericField>(extendedCopyrightYearID, 1);
}

SpcNumericField SpcFile::IntroLength() const
{
    if (extendedTag.introLength != nullptr)
        return *extendedTag.introLength;
    else
        return *InitField<SpcNumericField>(extendedIntroLengthID, 1);
}

SpcNumericField SpcFile::LoopLength() const
{
    if (extendedTag.loopLength != nullptr)
        return *extendedTag.loopLength;
    else
        return *InitField<SpcNumericField>(extendedLoopLengthID, 1);
}

SpcNumericField SpcFile::EndLength() const
{
    if (extendedTag.endLength != nullptr)
        return *extendedTag.endLength;
    else
        return *InitField<SpcNumericField>(extendedEndLengthID, 1);
}

SpcBinaryField SpcFile::MutedVoices() const
{
    if (extendedTag.mutedVoices != nullptr)
        return *extendedTag.mutedVoices;
    else
        return *InitField<SpcBinaryField>(extendedMutedVoicesID, 1);
}

SpcNumericField SpcFile::LoopTimes() const
{
    if (extendedTag.loopTimes != nullptr)
        return *extendedTag.loopTimes;
    else
        return *InitField<SpcNumericField>(extendedLoopTimesID, 1);
}

SpcNumericField SpcFile::PreampLevel() const
{
    if (extendedTag.preampLevel != nullptr)
        return *extendedTag.preampLevel;
    else
        return *InitField<SpcNumericField>(extendedPreampLevelID, 1);
}

bool SpcFile::Load()
{
    // Initialize the extended tag; sets all members to nulltpr.
    extendedTag = ID666ExtendedTag();

    SpcFileStream file{ fileName };
    file.Open(Binary::FileMode::Read);

    if (!file.IsOpen())
        return false;

    file.Read(&header);

    if (file.HeaderContainsTag())
    {
        headerContainsTag = true;

        if (file.HasBinaryTag())
        {
            hasBinaryTag = true;
            file.Read(&binaryTag);
        }
        else
        {
            file.Read(&textTag);
        }
    }

    if (file.HasExtendedTag())
    {
        hasExtendedTag = true;
        file.SeekExtendedTag();
        Binary::ChunkHeader tagHeader;
        file.Read(&tagHeader);
        std::string id = tagHeader.id.Value();
        std::string size = tagHeader.dataSize.ToString();
        size_t sizeRemaining = tagHeader.dataSize.Value();

        while (sizeRemaining > 0)
        {
            ExtendedID666Item item;
            file.Read(&item);

            switch (item.type.Value())
            {
                case extendedTypeDataInHeader:
                    sizeRemaining -= item.Size();
                    LoadHeaderField(item);
                    break;
                case extendedTypeString:
                {
                    size_t dataSize = item.data.Value();
                    sizeRemaining -= item.Size();
                    sizeRemaining -= dataSize;
                    LoadTextField(item, file);

                    if (dataSize % 4 != 0)
                    {
                        size_t paddingSize = 1;

                        while ((dataSize + paddingSize) % 4 != 0)
                            paddingSize++;

                        Binary::RawField padding{ paddingSize };
                        file.Read(&padding);
                        sizeRemaining -= paddingSize;
                    }

                    break;
                }
                case extendedTypeInteger:
                {
                    sizeRemaining -= item.Size();
                    sizeRemaining -= item.data.Value();
                    LoadNumericField(item, file);                    
                    break;
                }
                default:
                    return false;
            }
        }
    }

    hasLoaded = true;
    return true;
}

void SpcFile::LoadHeaderField(ExtendedID666Item& item)
{
    constexpr size_t offset{ extendedTagOffset };
    constexpr size_t size{ extendedTagDataSize };
    const uintmax_t id{ item.id.Value() };

    switch (id)
    {
        case extendedEmulatorUsedID:
            extendedTag.emulatorUsed = InitField<SpcEmulatorField>(id, size);
            std::memcpy(extendedTag.emulatorUsed->Data(), item.data.Data(), size);
            break;
        case extendedOSTDiscID:
            extendedTag.ostDisc = InitField<SpcNumericField>(id, size);
            std::memcpy(extendedTag.ostDisc->Data(), item.data.Data(), size);
            break;
        case extendedOSTTrackID:
            extendedTag.ostTrack = InitField<SpcTrackField>(id, size);
            std::memcpy(extendedTag.ostTrack->Data(), item.data.Data(), size);
            break;
        case extendedCopyrightYearID:
            extendedTag.copyrightYear = InitField<SpcNumericField>(id, size);
            std::memcpy(extendedTag.copyrightYear->Data(), item.data.Data(), size);
            break;
        case extendedMutedVoicesID:
            extendedTag.mutedVoices = InitField<SpcBinaryField>(id, size);
            std::memcpy(extendedTag.mutedVoices->Data(), item.data.Data(), size);
            break;
        case extendedLoopTimesID:
            extendedTag.loopTimes = InitField<SpcNumericField>(id, size);
            std::memcpy(extendedTag.loopTimes->Data(), item.data.Data(), size);
            break;
    }
}

void SpcFile::LoadTextField(ExtendedID666Item& item, SpcFileStream& stream)
{
    constexpr uintmax_t offset{ extendedTagOffset };
    const uintmax_t size{ item.data.Value() };
    const uintmax_t id{ item.id.Value() };

    switch (item.id.Value())
    {
        case extendedSongNameID:
            extendedTag.songName = InitField<SpcTextField>(id, size);
            stream.Read(extendedTag.songName.get());
            break;
        case extendedGameNameID:
            extendedTag.gameName = InitField<SpcTextField>(id, size);
            stream.Read(extendedTag.gameName.get());
            break;
        case extendedArtistNameID:
            extendedTag.artistName = InitField<SpcTextField>(id, size);
            stream.Read(extendedTag.artistName.get());
            break;
        case extendedDumperNameID:
            extendedTag.dumperName = InitField<SpcTextField>(id, size);
            stream.Read(extendedTag.dumperName.get());
            break;
        case extendedCommentsID:
            extendedTag.comments = InitField<SpcTextField>(id, size);
            stream.Read(extendedTag.comments.get());
            break;
        case extendedOSTTitleID:
            extendedTag.ostTitle = InitField<SpcTextField>(id, size);
            stream.Read(extendedTag.ostTitle.get());
            break;
        case extendedPublisherNameID:
            extendedTag.publisherName = InitField<SpcTextField>(id, size);
            stream.Read(extendedTag.publisherName.get());
            break;
    }
}

void SpcFile::LoadNumericField(ExtendedID666Item& item, SpcFileStream& stream)
{
    constexpr uintmax_t offset{ extendedTagOffset };
    const uintmax_t size{ item.data.Value() };
    const uintmax_t id{ item.id.Value() };

    switch (id)
    {
        case extendedDateDumpedID:
            extendedTag.dateDumped = InitField<SpcDateField>(id, size);
            stream.Read(extendedTag.dateDumped.get());
            break;
        case extendedIntroLengthID:
            extendedTag.introLength =InitField<SpcNumericField>(id, size);
            stream.Read(extendedTag.introLength.get());
            break;
        case extendedLoopLengthID:
            extendedTag.loopLength = InitField<SpcNumericField>(id, size);
            stream.Read(extendedTag.loopLength.get());
            break;
        case extendedEndLengthID:
            extendedTag.endLength = InitField<SpcNumericField>(id, size);
            stream.Read(extendedTag.endLength.get());
            break;
        case extendedFadeLengthID:
            extendedTag.fadeLength = InitField<SpcNumericField>(id, size);
            stream.Read(extendedTag.fadeLength.get());
            break;
        case extendedPreampLevelID:
            extendedTag.preampLevel = InitField<SpcNumericField>(id, size);
            stream.Read(extendedTag.preampLevel.get());
            break;
    }
}