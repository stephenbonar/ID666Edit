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

void PadItem(ID666ExtendedItem* item)
{
    auto size = std::static_pointer_cast<SpcNumericField>(item->data);

    if (size->Value() % 4 != 0)
    {
        size_t paddingSize = 1;

        while ((size->Value() + paddingSize) % 4 != 0)
            paddingSize++;

        item->padding = std::make_shared<SpcTextField>(
            "<padding>", extendedTagOffset, paddingSize);
    }
}

SpcTextField SpcFile::SongTitle() const
{
    return GetField<SpcTextField>(binaryTag.songTitle,
                                  textTag.songTitle, 
                                  extendedTag.songName.get());
}

SpcTextField SpcFile::GameTitle() const
{
    return GetField<SpcTextField>(binaryTag.gameTitle,
                                  textTag.gameTitle, 
                                  extendedTag.gameName.get());
}

SpcTextField SpcFile::DumperName() const
{
    return GetField<SpcTextField>(binaryTag.dumperName,
                                  textTag.dumperName, 
                                  extendedTag.dumperName.get());
}

SpcTextField SpcFile::Comments() const
{
    return GetField<SpcTextField>(binaryTag.comments,
                                  textTag.comments, 
                                  extendedTag.comments.get());
}

SpcDateField SpcFile::DateDumped() const
{
    return GetField<SpcDateField>(binaryTag.dateDumped,
                                  textTag.dateDumped, 
                                  extendedTag.dateDumped.get());
}

SpcNumericField SpcFile::SongLength() const
{
    return GetField<SpcNumericField>(binaryTag.songLength, textTag.songLength);
}

SpcNumericField SpcFile::FadeLength() const
{
    return GetField<SpcNumericField>(binaryTag.fadeLength, textTag.fadeLength);
}

SpcTextField SpcFile::SongArtist() const
{
    return GetField<SpcTextField>(binaryTag.songArtist, 
                                  textTag.songArtist, 
                                  extendedTag.artistName.get());
}

SpcNumericField SpcFile::DefaultChannelDisables() const
{
    return GetField<SpcNumericField>(binaryTag.defaultChannelState, 
                                     textTag.defaultChannelState);
}

SpcEmulatorField SpcFile::EmulatorUsed() const
{
    return GetField<SpcEmulatorField>(binaryTag.emulatorUsed, 
                                      textTag.emulatorUsed, 
                                      extendedTag.emulatorUsed.get());
}

SpcTextField SpcFile::OstTitle() const
{
    return GetField<SpcTextField>(extendedTag.ostTitle.get(), 
                                  extendedOSTTitleID, 
                                  1);
}

SpcNumericField SpcFile::OstDisc() const
{
    return GetField<SpcNumericField>(extendedTag.ostDisc.get(),
                                     extendedOSTDiscID,
                                     4);
}

SpcTrackField SpcFile::OstTrack() const
{
    return GetField<SpcTrackField>(extendedTag.ostTrack.get(), 
                                   extendedOSTTrackID, 
                                   1);
}

SpcTextField SpcFile::PublisherName() const
{
    return GetField<SpcTextField>(extendedTag.publisherName.get(), 
                                  extendedPublisherNameID, 
                                  1);
}

SpcNumericField SpcFile::CopyrightYear() const
{
    return GetField<SpcNumericField>(extendedTag.copyrightYear.get(), 
                                     extendedCopyrightYearID, 
                                     1);
}

SpcNumericField SpcFile::IntroLength() const
{
    return GetField<SpcNumericField>(extendedTag.introLength.get(), 
                                     extendedIntroLengthID, 
                                     1);
}

SpcNumericField SpcFile::LoopLength() const
{
    return GetField<SpcNumericField>(extendedTag.loopLength.get(), 
                                     extendedLoopLengthID, 
                                     1);
}

SpcNumericField SpcFile::EndLength() const
{
    return GetField<SpcNumericField>(extendedTag.endLength.get(), extendedEndLengthID, 1);
}

SpcBinaryField SpcFile::MutedVoices() const
{
    return GetField<SpcBinaryField>(extendedTag.mutedVoices.get(), 
                                    extendedMutedVoicesID, 
                                    1);
}

SpcNumericField SpcFile::LoopTimes() const
{
    return GetField<SpcNumericField>(extendedTag.loopTimes.get(), 
                                     extendedLoopLengthID, 
                                     1);
}

SpcNumericField SpcFile::PreampLevel() const
{
    return GetField<SpcNumericField>(extendedTag.preampLevel.get(), 
                                     extendedPreampLevelID, 
                                     1);
}

void SpcFile::SetSongTitle(std::string value)
{
    SetCommand<SpcTextField> command;
    command.binaryField = &binaryTag.songTitle;
    command.textField = &textTag.songTitle;
    command.extendedID = extendedSongNameID;
    command.extendedType = extendedTypeString;
    command.value = value;
    SetField<SpcTextField>(command, extendedTag.songName);
}

void SpcFile::SetGameTitle(std::string value)
{
    SetCommand<SpcTextField> command;
    command.binaryField = &binaryTag.gameTitle;
    command.textField = &textTag.gameTitle;
    command.extendedID = extendedGameNameID;
    command.extendedType = extendedTypeString;
    command.value = value;
    SetField<SpcTextField>(command, extendedTag.gameName);
}

void SpcFile::SetDumperName(std::string value)
{
    SetCommand<SpcTextField> command;
    command.binaryField = &binaryTag.dumperName;
    command.textField = &textTag.dumperName;
    command.extendedID = extendedDumperNameID;
    command.extendedType = extendedTypeString;
    command.value = value;
    SetField<SpcTextField>(command, extendedTag.dumperName);
}

void SpcFile::SetComments(std::string value)
{
    SetCommand<SpcTextField> command;
    command.binaryField = &binaryTag.comments;
    command.textField = &textTag.comments;
    command.extendedID = extendedCommentsID;
    command.extendedType = extendedTypeString;
    command.value = value;
    SetField<SpcTextField>(command, extendedTag.comments);
}

void SpcFile::SetDateDumped(std::string value)
{
    if (tagType == ID666TagType::Binary)
        binaryTag.dateDumped.SetBinaryValue(value);
    else
        textTag.dateDumped.SetTextValue(value);
}

void SpcFile::SetSongLength(std::string value)
{
    SetCommand<SpcNumericField> command;
    command.binaryField = &binaryTag.songLength;
    command.textField = &textTag.songLength;
    command.value = value;
    SpcNumericField* songLength;
    SetField<SpcNumericField>(command, songLength);
}

void SpcFile::SetFadeLength(std::string value)
{

}

void SpcFile::SetSongArtist(std::string value)
{

}

void SpcFile::SetDefaultChannelDisables(std::string value)
{

}

void SpcFile::SetEmulatorUsed(std::string value)
{

}

void SpcFile::SetOstTitle(std::string value)
{

}

void SpcFile::SetOstDisc(std::string value)
{
    
}

void SpcFile::SetOstTrack(std::string value)
{

}

void SpcFile::SetPublisherName(std::string value)
{

}

void SpcFile::SetCopyrightYear(std::string value)
{

}

void SpcFile::SetIntroLength(std::string value)
{

}

void SpcFile::SetLoopLength(std::string value)
{

}

void SpcFile::SetEndLength(std::string value)
{

}

void SpcFile::SetMutedVoices(std::string value)
{

}

void SpcFile::SetLoopTimes(std::string value)
{

}

void SpcFile::SetPreampLevel(std::string value)
{

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
        tagType = file.TagType();

        if (tagType == ID666TagType::Binary)
        {
            file.Read(&binaryTag);
        }
        else
        {
            file.Read(&textTag);

            if (tagType == ID666TagType::TextMixed)
            {
                textTag.songLength.SetType(SpcNumericType::Binary);
                textTag.fadeLength.SetType(SpcNumericType::Binary);
            }
        }
    }

    file.Read(&spcRam);
    file.Read(&dspRegisters);
    file.Read(&unused);
    file.Read(&extraRam);

    if (file.HasExtendedTag())
    {
        hasExtendedTag = true;
        file.Read(&extendedTagHeader);
        std::string id = extendedTagHeader.id.Value();
        std::string size = extendedTagHeader.dataSize.ToString();
        size_t sizeRemaining = extendedTagHeader.dataSize.Value();

        while (sizeRemaining > 0)
        {
            auto item = std::make_shared<ID666ExtendedItem>();
            file.Read(item.get());

            switch (item->type->Value())
            {
                case extendedTypeDataInHeader:
                    item->data->SetLabel(
                        extendedFieldLabels.at(item->id->Value()));
                    sizeRemaining -= item->Size();
                    LoadHeaderItem(item);
                    break;
                case extendedTypeString:
                {
                    item->data->SetLabel("Item Length");
                    auto data = std::static_pointer_cast<SpcNumericField>(
                        item->data);
                    size_t dataSize = data->Value();
                    sizeRemaining -= item->Size();
                    sizeRemaining -= dataSize;
                    LoadTextItem(item, file);
                    PadItem(item.get());

                    if (item->padding != nullptr)
                    {
                        file.Read(item->padding.get());
                        sizeRemaining -= item->padding->Size();
                    }

                    break;
                }
                case extendedTypeInteger:
                {
                    item->data->SetLabel("Item Length");
                    sizeRemaining -= item->Size();
                    auto data = std::static_pointer_cast<SpcNumericField>(
                        item->data);
                    sizeRemaining -= data->Value();
                    LoadNumericItem(item, file);                    
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

bool SpcFile::Save()
{
    if (!hasLoaded)
        return false;

    SpcFileStream stream{ fileName };
    stream.Open(Binary::FileMode::Write);

    if (!stream.IsOpen())
        return false;

    stream.Write(&header);

    if (tagType == ID666TagType::Binary)
        stream.Write(&binaryTag);
    else
        stream.Write(&textTag);

    stream.Write(&spcRam);
    stream.Write(&dspRegisters);
    stream.Write(&unused);
    stream.Write(&extraRam);

    if (hasExtendedTag)
    {
        extendedTagHeader.dataSize.SetValue(extendedTag.Size());
        stream.Write(&extendedTagHeader);
        stream.Write(&extendedTag);
    }

    return true;
}

void SpcFile::LoadHeaderItem(std::shared_ptr<ID666ExtendedItem> item)
{
    switch (item->id->Value())
    {
        case extendedEmulatorUsedID:
        {
            std::string label = extendedFieldLabels.at(item->id->Value());
            auto data = std::make_shared<SpcEmulatorField>(
                label, 
                extendedTagOffset, 
                extendedTagDataSize);
            std::memcpy(data->Data(), item->data->Data(), extendedTagDataSize); 
            item->data = data;
            extendedTag.emulatorUsed = item;
            break;
        }
        case extendedOSTDiscID:
            extendedTag.ostDisc = item;
            break;
        case extendedOSTTrackID:
        {
            std::string label = extendedFieldLabels.at(item->id->Value());
            auto data = std::make_shared<SpcTrackField>(label, 
                                                        extendedTagOffset, 
                                                        extendedTagDataSize);
            std::memcpy(data->Data(), item->data->Data(), extendedTagDataSize); 
            item->data = data;
            extendedTag.ostTrack = item;
            break;
        }
        case extendedCopyrightYearID:
            extendedTag.copyrightYear = item;
            break;
        case extendedMutedVoicesID:
        {
            std::string label = extendedFieldLabels.at(item->id->Value());
            auto data = std::make_shared<SpcBinaryField>(label, 
                                                         extendedTagOffset, 
                                                         extendedTagDataSize);
            std::memcpy(data->Data(), item->data->Data(), extendedTagDataSize); 
            item->data = data;
            extendedTag.mutedVoices = item;
            break;
        }
        case extendedLoopTimesID:
            extendedTag.loopTimes = item;
            break;
    }
}

void SpcFile::LoadTextItem(std::shared_ptr<ID666ExtendedItem> item, 
                           SpcFileStream& stream)
{
    auto data = std::static_pointer_cast<SpcNumericField>(item->data);
    const uintmax_t size{ data->Value() };
    const uintmax_t id{ item->id->Value() };

    switch (id)
    {
        case extendedSongNameID:
            item->extendedData = InitField<SpcTextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.songName = item;
            break;
        case extendedGameNameID:
            item->extendedData = InitField<SpcTextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.gameName = item;
            break;
        case extendedArtistNameID:
            item->extendedData = InitField<SpcTextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.artistName = item;
            break;
        case extendedDumperNameID:
            item->extendedData = InitField<SpcTextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.dumperName = item;
            break;
        case extendedCommentsID:
            item->extendedData = InitField<SpcTextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.comments = item;
            break;
        case extendedOSTTitleID:
            item->extendedData = InitField<SpcTextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.ostTitle = item;
            break;
        case extendedPublisherNameID:
            item->extendedData = InitField<SpcTextField>(id, size);
            stream.Read(item->extendedData.get());
            extendedTag.publisherName = item;
            break;
    }
}

void SpcFile::LoadNumericItem(std::shared_ptr<ID666ExtendedItem> item, 
                              SpcFileStream& stream)
{
    //constexpr uintmax_t offset{ extendedTagOffset };
    auto data = std::static_pointer_cast<SpcNumericField>(item->data);
    const uintmax_t size{ data->Value() };
    const uintmax_t id{ item->id->Value() };

    switch (id)
    {
        case extendedDateDumpedID:
            item->extendedData = InitField<SpcDateField>(id, size);
            extendedTag.dateDumped = item;
            stream.Read(item->extendedData.get());
            break;
        case extendedIntroLengthID:
            item->extendedData = InitField<SpcNumericField>(id, size);
            extendedTag.introLength = item;
            stream.Read(item->extendedData.get());
            break;
        case extendedLoopLengthID:
            item->extendedData = InitField<SpcNumericField>(id, size);
            extendedTag.loopLength = item;
            stream.Read(item->extendedData.get());
            break;
        case extendedEndLengthID:
            item->extendedData = InitField<SpcNumericField>(id, size);
            extendedTag.endLength = item;
            stream.Read(item->extendedData.get());
            break;
        case extendedFadeLengthID:
            item->extendedData = InitField<SpcNumericField>(id, size);
            extendedTag.fadeLength = item;
            stream.Read(item->extendedData.get());
            break;
        case extendedPreampLevelID:
            item->extendedData = InitField<SpcNumericField>(id, size);
            extendedTag.preampLevel = item;
            stream.Read(item->extendedData.get());
            break;
    }
}