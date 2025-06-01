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
#include <map>
#include "SpcHeader.h"
#include "ID666BinaryTag.h"
#include "ID666TextTag.h"
#include "ID666ExtendedTag.h"
#include "ID666ExtendedItem.h"
#include "SetCommand.h"
#include "SpcFileStream.h"

template<typename T>
std::shared_ptr<T> InitField(int extendedID, size_t size)
{
    std::string label = "<Unknown Field>";
    constexpr uintmax_t offset{ extendedTagOffset };

    if (extendedFieldLabels.find(extendedID) != extendedFieldLabels.end())
        label = extendedFieldLabels.at(extendedID);

    return std::make_shared<T>(label, offset, size);
}

void PadItem(ID666ExtendedItem* item);

/*
template<typename T>
std::shared_ptr<ID666ExtendedItem> InitItem(int extendedID, size_t size)
{
    auto item = std::make_shared<ID666ExtendedItem>();
    item->extendedData = InitItem<T>(extendedID, size);
    return item;
}
*/

class SpcFile
{
public:
    SpcFile(std::string fileName) : 
        fileName{ fileName }, 
        hasLoaded{ false }, 
        hasBinaryTag{ false },
        hasExtendedTag{ false },
        headerContainsTag{ false },
        spcRam{ 65536 },
        dspRegisters{ 128 },
        unused{ 64 },
        extraRam{ 64 }
    {}

    std::string FileName() const { return fileName; }

    bool HasLoaded() const { return hasLoaded; }

    bool HasBinaryTag() const { return hasBinaryTag; }

    bool HasExtendedTag() const { return hasExtendedTag; }

    bool HeaderContainsTag() const { return headerContainsTag; }

    SpcHeader Header() const { return header; }

    ID666BinaryTag BinaryTag() const { return binaryTag; }

    ID666TextTag TextTag() const { return textTag; }

    Binary::ChunkHeader ExtendedTagHeader() const { return extendedTagHeader; }

    ID666ExtendedTag ExtendedTag() const { return extendedTag; }

    SpcTextField SongTitle() const;

    SpcTextField GameTitle() const;

    SpcTextField DumperName() const;

    SpcTextField Comments() const;

    SpcDateField DateDumped() const;

    SpcNumericField SongLength() const;

    SpcNumericField FadeLength() const;

    SpcTextField SongArtist() const;

    SpcNumericField DefaultChannelDisables() const;

    SpcEmulatorField EmulatorUsed() const;

    SpcTextField OstTitle() const;

    SpcNumericField OstDisc() const;

    SpcTrackField OstTrack() const;

    SpcTextField PublisherName() const;

    SpcNumericField CopyrightYear() const;

    SpcNumericField IntroLength() const;

    SpcNumericField LoopLength() const;

    SpcNumericField EndLength() const;

    SpcBinaryField MutedVoices() const;

    SpcNumericField LoopTimes() const;

    SpcNumericField PreampLevel() const;

    void SetSongTitle(std::string value);

    void SetGameTitle(std::string value);

    void SetDumperName(std::string value);

    void SetComments(std::string value);

    void SetDateDumped(std::string value);

    void SetSongLength(std::string value);

    void SetFadeLength(std::string value);

    void SetSongArtist(std::string value);

    void SetDefaultChannelDisables(std::string value);

    void SetEmulatorUsed(std::string value);

    void SetOstTitle(std::string value);

    void SetOstDisc(std::string value);

    void SetOstTrack(std::string value);

    void SetPublisherName(std::string value);

    void SetCopyrightYear(std::string value);

    void SetIntroLength(std::string value);

    void SetLoopLength(std::string value);

    void SetEndLength(std::string value);

    void SetMutedVoices(std::string value);

    void SetLoopTimes(std::string value);

    void SetPreampLevel(std::string value);

    bool Load();

    bool Save();
private:
    std::string fileName;
    bool hasLoaded;
    bool hasBinaryTag;
    bool hasExtendedTag;
    bool headerContainsTag;
    SpcHeader header;
    ID666BinaryTag binaryTag;
    ID666TextTag textTag;
    Binary::RawField spcRam;
    Binary::RawField dspRegisters;
    Binary::RawField unused;
    Binary::RawField extraRam;
    Binary::ChunkHeader extendedTagHeader;
    ID666ExtendedTag extendedTag;

    template<typename T>
    T GetField(const T& binaryField, const T& textField) const
    {
        if (hasBinaryTag)
            return binaryField;
        else
            return textField;
    }

    template<typename T>
    T GetField(ID666ExtendedItem* item, int id, int defaultSize) const
    {
        if (item != nullptr)
        {
            if (item->type->Value() == extendedTypeDataInHeader)
            {
                auto field = InitField<T>(id, extendedTagDataSize);

                for (int i = 0; i < extendedTagDataSize; i++)
                    field->Data()[i] = item->data->Data()[i];

                return *field;
            }

            if (item->extendedData != nullptr)
            {
                SpcField* field = item->extendedData.get();
                T* convertedField = dynamic_cast<T*>(field);
                return *convertedField;
            }
        }

        return *InitField<T>(id, defaultSize);
    }

    template<typename T>
    T GetField(const T& binaryField, 
               const T& textField, 
               ID666ExtendedItem* item) const
    {
        if (item != nullptr)
        {
            if (item->extendedData != nullptr)
            {
                SpcField* field = item->extendedData.get();
                T* convertedField = dynamic_cast<T*>(field);
                return *convertedField;
            }
        }
        
        if (hasBinaryTag)
        {
            return binaryField;
        }
        else
        {
            return textField;
        }
    }

    template<typename T>
    void SetField(SetCommand<T> cmd, std::shared_ptr<ID666ExtendedItem>& item)
    {
        T* field;

        if (hasBinaryTag)
            field = cmd.binaryField;
        else
            field = cmd.textField;

        field->SetValue(cmd.value);

        if (cmd.value.size() > field->Size())
        {
            auto data = InitField<T>(cmd.extendedID, cmd.value.size());
            hasExtendedTag = true;

            if (item == nullptr)
            {
                item = std::make_shared<ID666ExtendedItem>();
                item->id->SetValue(cmd.extendedID);
                item->type->SetValue(cmd.extendedType);
                auto size = std::static_pointer_cast<SpcNumericField>(
                    item->data);
                size->SetValue(cmd.value.size());
                PadItem(item.get());
            }

            data->SetValue(cmd.value);
            item->extendedData = data;
        }
        else if (item != nullptr)
        {
            item = nullptr;
        }
    }

    void LoadHeaderItem(std::shared_ptr<ID666ExtendedItem> item);

    void LoadTextItem(std::shared_ptr<ID666ExtendedItem> item, 
                      SpcFileStream& stream);

    void LoadNumericItem(std::shared_ptr<ID666ExtendedItem> item, 
                         SpcFileStream& stream);
};

#endif