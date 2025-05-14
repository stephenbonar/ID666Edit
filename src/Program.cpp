// Program.cpp - Defines the Program class.
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

#include "Program.h"

void Program::PrintProgramInfo()
{
    std::cout << "ID666Edit v0.1" << std::endl;
    std::cout << "Copyright (C) 2025 Stephen Bonar" << std::endl << std::endl;
}

void Program::DefineCmdLineParameters()
{
    CmdLine::ProgParam::Definition progParamDef;
    progParamDef.name = "ID666Edit";
    progParamDef.description = "An ID666 metadata tag editor for .SPC files.";
    progParam = std::make_unique<CmdLine::ProgParam>(progParamDef);

    CmdLine::PosParam::Definition spcFileParamDef;
    spcFileParamDef.name = "spc_file";
    spcFileParamDef.description = "The SPC file to open.";
    spcFileParamDef.isMandatory = true;
    spcFileParam = std::make_unique<CmdLine::PosParam>(spcFileParamDef);
}

void Program::InitializeCmdLineParser(std::vector<std::string> arguments)
{
    parser = std::make_unique<CmdLine::Parser>(progParam.get(), arguments);
    parser->Add(spcFileParam.get());
}

int Program::SelectMode()
{
    if (spcFileParam->IsSpecified())
    {
        return PrintSpcFile();
    }
    else
    {
        return 1;
    }
}

int Program::PrintSpcFile()
{
    SpcFileStream file{ spcFileParam->Value() };
    SpcHeader header;
    file.Open(Binary::FileMode::Read);

    if (!file.IsOpen())
    {
        std::cerr << "ERROR: unable to open file." << std::endl;
        return 2;
    }

    file.Read(&header);
    std::cout << header.ToString() << std::endl;

    if (file.HeaderContainsTag())
    {
        std::cout << FormatValue("Header Contains Tag", "True") << std::endl;

        if (file.HasBinaryTag())
            PrintBinaryTag(file);
        else
            PrintTextTag(file);
    }
    else
    {
        std::cout << FormatValue("Header Contains Tag", "False") << std::endl;
    }

    if (file.HasExtendedTag())
    {
        PrintExtendedTag(file);
    }
    else
    {
        std::cout << FormatValue("Has Extended Tag", "False") << std::endl;
    }

    std::cout << std::endl;
    return 0;
}

void Program::PrintTextTag(SpcFileStream& file)
{
    std::cout << FormatValue("Tag Type", "Text") << std::endl;
    std::cout << std::endl;

    ID666TextTag tag;
    file.Read(&tag);
    std::cout << tag.ToString() << std::endl;
}

void Program::PrintBinaryTag(SpcFileStream& file)
{
    std::cout << FormatValue("Tag Type", "Binary") << std::endl;
    std::cout << std::endl;

    ID666BinaryTag tag;
    file.Read(&tag);
    std::cout << tag.ToString() << std::endl;
}

void Program::PrintExtendedTag(SpcFileStream& file)
{
    std::cout << FormatValue("Has Extended Tag", "True") << std::endl;
    file.SeekExtendedTag();

    Binary::ChunkHeader tagHeader;
    file.Read(&tagHeader);
    std::string id = tagHeader.id.Value();
    std::string size = tagHeader.dataSize.ToString();
    size_t sizeRemaining = tagHeader.dataSize.Value();
    std::cout << FormatValue("Extended Tag ID", id) << std::endl;
    std::cout << FormatValue("Extended Tag Size", size) << std::endl;

    while (sizeRemaining > 0)
    {
        ExtendedID666Item item;
        file.Read(&item);

        switch (item.type.Value())
        {
            case extendedTypeDataInHeader:
                sizeRemaining -= item.Size();
                PrintExtendedItem(item);
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

void Program::PrintExtendedItem(ExtendedID666Item& item)
{
    switch (item.id.Value())
    {
        case extendedEmulatorUsedID:
            std::cout << FormatValue("Emulator Used", item.data.ToString());
            break;
        case extendedOSTDiskID:
            std::cout << FormatValue("OST Disc", item.data.ToString());
            break;
        case extendedOSTTrackID:
        {
            std::stringstream stream;

            // The extended track has an optional character in the first byte
            // and the track number in the second byte. This is so you can
            // do things like Track 1a, Track 1b, etc.
            char trackChar = item.data.Data()[0];
            int trackNo = static_cast<int>(item.data.Data()[1]);

            stream << trackNo << trackChar;
            std::cout << FormatValue("OST Track", stream.str());
            break;
        }
        case extendedCopyrightYearID:
            std::cout << FormatValue("Copyright Year", item.data.ToString());
            break;
        case extendedMutedVoicesID:
            std::cout << FormatValue("Muted Voices", 
                item.data.ToString(Binary::StringFormat::Bin));
            break;
        case extendedLoopTimesID:
            std::cout << FormatValue("Loop Times", item.data.ToString());
            break;
        case extendedPreampLevelID:
            std::cout << FormatValue("Preamp Level", item.data.ToString());
            break;
        default:
            std::cerr << "Invalid extended item ID. File may be corrupt.";
    }

    std::cout << std::endl;
}

void Program::PrintExtendedItem(ExtendedID666Item& item, 
    Binary::StringField& field)
{
    switch (item.id.Value())
    {
        case extendedSongNameID:
            std::cout << FormatValue("Song Name", field.Value());
            break;
        case extendedGameNameID:
            std::cout << FormatValue("Game Name", field.Value());
            break;
        case extendedArtistNameID:
            std::cout << FormatValue("Artist", field.Value());
            break;
        case extendedDumperNameID:
            std::cout << FormatValue("Dumper", field.Value());
            break;
        case extendedCommentsID:
            std::cout << FormatValue("Comments", field.Value());
            break;
        case extendedOSTTitleID:
            std::cout << FormatValue("OST Title", field.Value());
            break;
        case extendedPublisherNameID:
            std::cout << FormatValue("Publisher", field.Value());
            break;
        default:
            std::cerr << "Invalid extended item ID. File may be corrupt.";
    }

    std::cout << std::endl;
}

void Program::PrintExtendedItem(ExtendedID666Item& item, 
    Binary::UInt32Field& field)
{
    switch (item.id.Value())
    {
        case extendedDateDumpedID:
            std::cout << FormatValue("Date Dumped", field.ToString());
            break;
        case extendedIntroLengthID:
            std::cout << FormatValue("Intro Length", field.ToString());
            break;
        case extendedLoopLengthID:
            std::cout << FormatValue("Loop Length", field.ToString());
            break;
        case extendedEndLengthID:
            std::cout << FormatValue("End Length", field.ToString());
            break;
        case extendedFadeLengthID:
            std::cout << FormatValue("Fade Length", field.ToString());
            break;
        default:
            std::cerr << "Invalid extended item ID. File may be corrupt.";
    }

    std::cout << std::endl;
}

int Program::Run(std::vector<std::string> arguments)
{
    PrintProgramInfo();
    DefineCmdLineParameters();
    InitializeCmdLineParser(arguments);
    CmdLine::Parser::Status status = parser->Parse();

    if (status == CmdLine::Parser::Status::Success)
    {
        return SelectMode();
    }
    else
    {
        std::cerr << parser->GenerateUsage();
        return 1;
    }
}