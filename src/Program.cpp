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

void Program::PrintVersion()
{
    std::cout << "ID666Edit v0.9" << std::endl;
    std::cout << "Copyright (C) 2025 Stephen Bonar" << std::endl << std::endl;
}

void Program::DefineParameters()
{
    CmdLine::ProgParam::Definition progDef;
    progDef.name = "id666edit";
    progDef.description = "An ID666 metadata tag editor for .SPC files";
    progParam = std::make_unique<CmdLine::ProgParam>(progDef);

    CmdLine::MultiPosParam::Definition fileDef;
    fileDef.name = "spcfile";
    fileDef.description = "The .spc file(s) to open";
    fileDef.isMandatory = true;
    spcFileParam = std::make_unique<CmdLine::MultiPosParam>(fileDef);

    CmdLine::ValueOption::Definition printDef;
    printDef.shortName = 'p';
    printDef.longName = "print";
    printDef.description = "Prints the specified item in the file(s)";
    printOption = std::make_unique<CmdLine::ValueOption>(printDef);

    CmdLine::ValueOption::Definition editDef;
    editDef.shortName = 'e';
    editDef.longName = "edit";
    editDef.description = "Edits the specified tag item (use \"name=value\")";
    editOption = std::make_unique<CmdLine::ValueOption>(editDef);

    CmdLine::ValueOption::Definition fileNameToTagDef;
    fileNameToTagDef.shortName = 'f';
    fileNameToTagDef.longName = "filename-to-tag";
    fileNameToTagDef.description = "Sets tags from filename using a pattern";
    fileNameToTagOption = std::make_unique<CmdLine::ValueOption>(
        fileNameToTagDef);

    CmdLine::ValueOption::Definition tagToFileNameDef;
    tagToFileNameDef.shortName = 't';
    tagToFileNameDef.longName = "tag-to-filename";
    tagToFileNameDef.description = "Sets file name to tag values using pattern";
    tagToFileNameOption = std::make_unique<CmdLine::ValueOption>(
        tagToFileNameDef);

    CmdLine::ValueOption::Definition incrementDef;
    incrementDef.shortName = 'i';
    incrementDef.longName = "increment-track";
    incrementDef.description = 
        "Increments track number by the specified amount";
    incrementOption = std::make_unique<CmdLine::ValueOption>(incrementDef);

    CmdLine::Option::Definition detailedDef;
    detailedDef.shortName = 'd';
    detailedDef.longName = "detailed";
    detailedDef.description = "Prints detailed information about the file(s)";
    detailedOption = std::make_unique<CmdLine::Option>(detailedDef);

    CmdLine::Option::Definition versionDef;
    versionDef.shortName = 'v';
    versionDef.longName = "version";
    versionDef.description = "Prints program version information";
    versionOption = std::make_unique<CmdLine::Option>(versionDef);

    CmdLine::OptionParam::Definition tagDef;
    tagDef.name = "tag";
    tagDef.description = "The entire ID666 tag";
    tagPrintParam = std::make_unique<CmdLine::OptionParam>(tagDef);
    printOption->Add(tagPrintParam.get());

    CmdLine::OptionParam::Definition headerDef;
    headerDef.name = "header";
    headerDef.description = "The .spc file header";
    headerPrintParam = std::make_unique<CmdLine::OptionParam>(headerDef);
    printOption->Add(headerPrintParam.get());

    CmdLine::OptionParam::Definition songDef;
    songDef.name = "song";
    songDef.description = "The name of the song";
    songPrintParam = std::make_unique<CmdLine::OptionParam>(songDef);
    songEditParam = std::make_unique<CmdLine::OptionParam>(songDef);
    printOption->Add(songPrintParam.get());
    editOption->Add(songEditParam.get());

    CmdLine::OptionParam::Definition gameDef;
    gameDef.name = "game";
    gameDef.description = "The name of the game";
    gamePrintParam = std::make_unique<CmdLine::OptionParam>(gameDef);
    gameEditParam = std::make_unique<CmdLine::OptionParam>(gameDef);
    printOption->Add(gamePrintParam.get());
    editOption->Add(gameEditParam.get());

    CmdLine::OptionParam::Definition dumperDef;
    dumperDef.name = "dumper";
    dumperDef.description = "The name of the person who dumped the song";
    dumperPrintParam = std::make_unique<CmdLine::OptionParam>(dumperDef);
    dumperEditParam = std::make_unique<CmdLine::OptionParam>(dumperDef);
    printOption->Add(dumperPrintParam.get());
    editOption->Add(dumperEditParam.get());

    CmdLine::OptionParam::Definition commentsDef;
    commentsDef.name = "comments";
    commentsDef.description = "The tagger's comments";
    commentsPrintParam = std::make_unique<CmdLine::OptionParam>(commentsDef);
    commentsEditParam = std::make_unique<CmdLine::OptionParam>(commentsDef);
    printOption->Add(commentsPrintParam.get());
    editOption->Add(commentsEditParam.get());

    CmdLine::OptionParam::Definition dateDef;
    dateDef.name = "date";
    dateDef.description = "The date the song was dumped";
    datePrintParam = std::make_unique<CmdLine::OptionParam>(dateDef);
    dateEditParam = std::make_unique<CmdLine::OptionParam>(dateDef);
    printOption->Add(datePrintParam.get());
    editOption->Add(dateEditParam.get());

    CmdLine::OptionParam::Definition songLengthDef;
    songLengthDef.name = "songlength";
    songLengthDef.description = "The length of the song, in seconds";
    songLengthPrintParam = std::make_unique<CmdLine::OptionParam>(
        songLengthDef);
    songLengthEditParam = std::make_unique<CmdLine::OptionParam>(
        songLengthDef);
    printOption->Add(songLengthPrintParam.get());
    editOption->Add(songLengthEditParam.get());

    CmdLine::OptionParam::Definition fadeLengthDef;
    fadeLengthDef.name = "fadelength";
    fadeLengthDef.description = "The length of fade out, in milliseconds";
    fadeLengthPrintParam = std::make_unique<CmdLine::OptionParam>(
        fadeLengthDef);
    fadeLengthEditParam = std::make_unique<CmdLine::OptionParam>(
        fadeLengthDef);
    printOption->Add(fadeLengthPrintParam.get());
    editOption->Add(fadeLengthEditParam.get());

    CmdLine::OptionParam::Definition artistDef;
    artistDef.name = "artist";
    artistDef.description = "The song artist / composer";
    artistPrintParam = std::make_unique<CmdLine::OptionParam>(artistDef);
    artistEditParam = std::make_unique<CmdLine::OptionParam>(artistDef);
    printOption->Add(artistPrintParam.get());
    editOption->Add(artistEditParam.get());

    CmdLine::OptionParam::Definition channelDef;
    channelDef.name = "channel";
    channelDef.description = 
        "Default channel state (0 = enabled, 1 = disabled)";
    channelPrintParam = std::make_unique<CmdLine::OptionParam>(channelDef);
    channelEditParam = std::make_unique<CmdLine::OptionParam>(channelDef);
    printOption->Add(channelPrintParam.get());
    editOption->Add(channelEditParam.get());

    CmdLine::OptionParam::Definition emulatorDef;
    emulatorDef.name = "emulator";
    emulatorDef.description = "The emulator used to dump the song";
    emulatorPrintParam = std::make_unique<CmdLine::OptionParam>(emulatorDef);
    emulatorEditParam = std::make_unique<CmdLine::OptionParam>(emulatorDef);
    printOption->Add(emulatorPrintParam.get());
    editOption->Add(emulatorEditParam.get());

    CmdLine::OptionParam::Definition titleDef;
    titleDef.name = "title";
    titleDef.description = "The Original Sound Track (OST) album title";
    titlePrintParam = std::make_unique<CmdLine::OptionParam>(titleDef);
    titleEditParam = std::make_unique<CmdLine::OptionParam>(titleDef);
    printOption->Add(titlePrintParam.get());
    editOption->Add(titleEditParam.get());

    CmdLine::OptionParam::Definition discDef;
    discDef.name = "disc";
    discDef.description = "The Original Sound Track (OST) disc number";
    discPrintParam = std::make_unique<CmdLine::OptionParam>(discDef);
    discEditParam = std::make_unique<CmdLine::OptionParam>(discDef);
    printOption->Add(discPrintParam.get());
    editOption->Add(discEditParam.get());

    CmdLine::OptionParam::Definition trackDef;
    trackDef.name = "track";
    trackDef.description = "The Original Sound Track (OST) from the tags";
    trackPrintParam = std::make_unique<CmdLine::OptionParam>(trackDef);
    trackEditParam = std::make_unique<CmdLine::OptionParam>(trackDef);
    printOption->Add(trackPrintParam.get());
    editOption->Add(trackEditParam.get());

    CmdLine::OptionParam::Definition publisherDef;
    publisherDef.name = "publisher";
    publisherDef.description = "The publisher of the game";
    publisherPrintParam = std::make_unique<CmdLine::OptionParam>(publisherDef);
    publisherEditParam = std::make_unique<CmdLine::OptionParam>(publisherDef);
    printOption->Add(publisherPrintParam.get());
    editOption->Add(publisherEditParam.get());

    CmdLine::OptionParam::Definition copyrightDef;
    copyrightDef.name = "copyright";
    copyrightDef.description = "The year the game was copyrighted";
    copyrightPrintParam = std::make_unique<CmdLine::OptionParam>(copyrightDef);
    copyrightEditParam = std::make_unique<CmdLine::OptionParam>(copyrightDef);
    printOption->Add(copyrightPrintParam.get());
    editOption->Add(copyrightEditParam.get());

    CmdLine::OptionParam::Definition introLengthDef;
    introLengthDef.name = "introlength";
    introLengthDef.description = "The length of the song intro, in ticks";
    introLengthPrintParam = std::make_unique<CmdLine::OptionParam>(
        introLengthDef);
    introLengthEditParam = std::make_unique<CmdLine::OptionParam>(
        introLengthDef);
    printOption->Add(introLengthPrintParam.get());
    editOption->Add(introLengthEditParam.get());

    CmdLine::OptionParam::Definition loopLengthDef;
    loopLengthDef.name = "looplength";
    loopLengthDef.description = "The length of each song loop, in ticks";
    loopLengthPrintParam = std::make_unique<CmdLine::OptionParam>(
        loopLengthDef);
    loopLengthEditParam = std::make_unique<CmdLine::OptionParam>(
        loopLengthDef);
    printOption->Add(loopLengthPrintParam.get());
    editOption->Add(loopLengthEditParam.get());

    CmdLine::OptionParam::Definition endLengthDef;
    endLengthDef.name = "endlength";
    endLengthDef.description = "The length of the end of the song, in ticks";
    endLengthPrintParam = std::make_unique<CmdLine::OptionParam>(endLengthDef);
    endLengthEditParam = std::make_unique<CmdLine::OptionParam>(endLengthDef);
    printOption->Add(endLengthPrintParam.get());
    editOption->Add(endLengthEditParam.get());

    CmdLine::OptionParam::Definition mutedDef;
    mutedDef.name = "muted";
    mutedDef.description = "8-bit value where each set bit mutes a voice";
    mutedPrintParam = std::make_unique<CmdLine::OptionParam>(mutedDef);
    mutedEditParam = std::make_unique<CmdLine::OptionParam>(mutedDef);
    printOption->Add(mutedPrintParam.get());
    editOption->Add(mutedEditParam.get());

    CmdLine::OptionParam::Definition loopTimesDef;
    loopTimesDef.name = "looptimes";
    loopTimesDef.description = "The number of times the song should loop";
    loopTimesPrintParam = std::make_unique<CmdLine::OptionParam>(loopTimesDef);
    loopTimesEditParam = std::make_unique<CmdLine::OptionParam>(loopTimesDef);
    printOption->Add(loopTimesPrintParam.get());
    editOption->Add(loopTimesEditParam.get());

    CmdLine::OptionParam::Definition preampDef;
    preampDef.name = "preamp";
    preampDef.description = "The preamp level to apply";
    preampPrintParam = std::make_unique<CmdLine::OptionParam>(preampDef);
    preampEditParam = std::make_unique<CmdLine::OptionParam>(preampDef);
    printOption->Add(preampPrintParam.get());
    editOption->Add(preampEditParam.get());
}

void Program::InitializeParser(std::vector<std::string> arguments)
{
    parser = std::make_unique<CmdLine::Parser>(progParam.get(), arguments);
    parser->Set(spcFileParam.get());
    parser->Add(printOption.get());
    parser->Add(editOption.get());
    parser->Add(fileNameToTagOption.get());
    parser->Add(tagToFileNameOption.get());
    parser->Add(detailedOption.get());
    parser->Add(incrementOption.get());
    parser->Add(versionOption.get());
}

int Program::SelectMode()
{
    if (versionOption->IsSpecified())
    {
        PrintVersion();
        return 0;
    }
    else if (spcFileParam->IsSpecified())
    {
        for (std::string value : spcFileParam->Values())
        {
            int result = 0;
            Spc::File file{ value };
        
            if (!file.Load())
            {
                std::cerr << "ERROR: unable to open file." << std::endl;
                return 2;
            }

            if (printOption->IsSpecified())
            {
                result = PrintSpecifiedItems(file);
            }
            else if (editOption->IsSpecified())
            {
                result = EditSpecifiedItems(file);
            }
            else if (fileNameToTagOption->IsSpecified())
            {
                file.FileNameToTag(fileNameToTagOption->Values()[0]);
            }
            else if (tagToFileNameOption->IsSpecified())
            {
                file.TagToFileName(tagToFileNameOption->Values()[0]);
            }
            else if (incrementOption->IsSpecified())
            {
                IncrementTrack(file);
            }
            else if (!printOption->IsSpecified() && !editOption->IsSpecified())
            {
                if (detailedOption->IsSpecified())
                    result = PrintSpcFileDetailed(file);
                else
                    result = PrintSpcFile(file);
            }

            if (result != 0)
                return result;
        }

        std::cout << "* indicates value is stored as extended tag data"
                  << std::endl;

        return 0;
    }
    else if (parser->BuiltInHelpOptionIsSpecified())
    {
        PrintVersion();
        std::cout << parser->GenerateHelp();
        return 0;
    }
    else
    {
        PrintVersion();
        std::cerr << parser->GenerateUsage();
        return 1;
    }
}

void Program::PrintSectionHeader(std::string title)
{
    PrintSectionHeader(title, title.length());
}

void Program::PrintSectionHeader(std::string title, int length)
{
    std::cout << title << std::endl;

    for (int i = 0; i < length; ++i)
        std::cout << '-';

    std::cout << std::endl;
}

void Program::PrintField(Spc::Field* field)
{
    std::cout << FormatField(field) << std::endl;
}

void Program::PrintField(Spc::TextField field)
{
    PrintField(&field);
}

void Program::PrintField(Spc::DateField field)
{
    PrintField(&field);
}

void Program::PrintField(Spc::NumericField field)
{
    PrintField(&field);
}

void Program::PrintField(Spc::TrackField field)
{
    PrintField(&field);
}

void Program::PrintField(Spc::EmulatorField field)
{
    PrintField(&field);
}

void Program::PrintField(Spc::BinaryField field)
{
    PrintField(&field);
}

int Program::PrintSpcFile(Spc::File& file)
{
    PrintSectionHeader(file.FileName(), 79);
    PrintField(file.SongTitle());
    PrintField(file.GameTitle());
    PrintField(file.DumperName());
    PrintField(file.Comments());
    PrintField(file.DateDumped());
    PrintField(file.SongLength());
    PrintField(file.FadeLength());
    PrintField(file.SongArtist());
    PrintField(file.DefaultChannelState());
    PrintField(file.EmulatorUsed());
    PrintField(file.OstTitle());
    PrintField(file.OstDisc());
    PrintField(file.OstTrack());
    PrintField(file.PublisherName());
    PrintField(file.CopyrightYear());
    PrintField(file.IntroLength());
    PrintField(file.LoopLength());
    PrintField(file.EndLength());
    PrintField(file.MutedVoices());
    PrintField(file.LoopTimes());
    PrintField(file.PreampLevel());
    std::cout << std::endl;
    return 0;
}

int Program::PrintSpcFileDetailed(Spc::File& file)
{
    PrintSectionHeader(file.FileName(), 79);
    std::cout << std::endl;
    PrintHeader(file);
    PrintTag(file);
    return 0;
}

void Program::PrintHeader(Spc::File& file)
{
    Spc::Header header = file.Header();
    PrintSectionHeader("SPC File Header");
    std::cout << header.ToString() << std::endl;
}

void Program::PrintTag(Spc::File& file)
{
    PrintSectionHeader("ID666 Tag");

    if (file.HeaderContainsTag())
    {
        std::cout << Spc::FormatValue("Header Contains Tag", "True") 
                  << std::endl;

        if (file.TagType() == Spc::TagType::Binary)
            PrintBinaryTag(file);
        else
            PrintTextTag(file);
    }
    else
    {
        std::cout << Spc::FormatValue("Header Contains Tag", "False") 
                  << std::endl;
    }

    if (file.HasExtendedTag())
    {
        PrintExtendedTag(file);
    }
    else
    {
        std::cout << Spc::FormatValue("Has Extended Tag", "False")
                  << std::endl;
    }
}

void Program::PrintTextTag(Spc::File& file)
{
    if (file.TagType() == Spc::TagType::Text)
        std::cout << Spc::FormatValue("Tag Type", "Text") << std::endl;
    else
        std::cout << Spc::FormatValue("Tag Type", "Text (Mixed)") << std::endl;

    Spc::TextTag tag = file.TextTag();
    std::cout << tag.ToString() << std::endl;
}

void Program::PrintBinaryTag(Spc::File& file)
{
    std::cout << Spc::FormatValue("Tag Type", "Binary") << std::endl;
    Spc::BinaryTag tag = file.BinaryTag();
    std::cout << tag.ToString() << std::endl;
}

void Program::PrintExtendedTag(Spc::File& file)
{
    PrintSectionHeader("Extended ID666 Tag");
    std::cout << Spc::FormatValue("Has Extended Tag", "True") << std::endl;
    Binary::ChunkHeader extendedTagHeader = file.ExtendedTagHeader();
    Spc::ExtendedTag tag = file.ExtendedTag();
    std::cout << Spc::FormatValue("IFF Chunk ID", 
                                  extendedTagHeader.id.ToString());
    std::cout << std::endl;
    std::cout << Spc::FormatValue("IFF Chunk Size",
                                  extendedTagHeader.dataSize.ToString());
    std::cout << std::endl;
    std::cout << tag.ToString() << std::endl;
}

int Program::PrintSpecifiedItems(Spc::File& file)
{
    PrintSectionHeader(file.FileName(), 79);

    if (headerPrintParam->IsSpecified())
        PrintHeader(file);

    if (tagPrintParam->IsSpecified())
        PrintTag(file);

    if (songPrintParam->IsSpecified())
        PrintField(file.SongTitle());

    if (gamePrintParam->IsSpecified())
        PrintField(file.GameTitle());

    if (dumperPrintParam->IsSpecified())
        PrintField(file.DumperName());

    if (commentsPrintParam->IsSpecified())
        PrintField(file.Comments());
    
    if (datePrintParam->IsSpecified())
        PrintField(file.DateDumped());

    if (songLengthPrintParam->IsSpecified())
        PrintField(file.SongLength());

    if (fadeLengthPrintParam->IsSpecified())
        PrintField(file.FadeLength());

    if (artistPrintParam->IsSpecified())
        PrintField(file.SongArtist());

    if (channelPrintParam->IsSpecified())
        PrintField(file.DefaultChannelState());

    if (emulatorPrintParam->IsSpecified())
        PrintField(file.EmulatorUsed());

    if (titlePrintParam->IsSpecified())
        PrintField(file.OstTitle());

    if (discPrintParam->IsSpecified())
        PrintField(file.OstDisc());

    if (trackPrintParam->IsSpecified())
        PrintField(file.OstTrack());

    if (publisherPrintParam->IsSpecified())
        PrintField(file.PublisherName());

    if (copyrightPrintParam->IsSpecified())
        PrintField(file.CopyrightYear());

    if (introLengthPrintParam->IsSpecified())
        PrintField(file.IntroLength());

    if (loopLengthPrintParam->IsSpecified())
        PrintField(file.LoopLength());

    if (endLengthPrintParam->IsSpecified())
        PrintField(file.EndLength());

    if (mutedPrintParam->IsSpecified())
        PrintField(file.MutedVoices());

    if (loopTimesPrintParam->IsSpecified())
        PrintField(file.LoopTimes());

    if (preampPrintParam->IsSpecified())
        PrintField(file.PreampLevel());

    std::cout << std::endl;

    return 0;
}

int Program::EditSpecifiedItems(Spc::File& file)
{
    PrintSectionHeader(file.FileName(), 79);

    if (songEditParam->IsSpecified())
    {
        file.SetSongTitle(songEditParam->Value());
        PrintField(file.SongTitle());
    }

    if (gameEditParam->IsSpecified())
    {
        file.SetGameTitle(gameEditParam->Value());
        PrintField(file.GameTitle());
    }

    if (dumperEditParam->IsSpecified())
    {
        file.SetDumperName(dumperEditParam->Value());
        PrintField(file.DumperName());
    }

    if (commentsEditParam->IsSpecified())
    {
        file.SetComments(commentsEditParam->Value());
        PrintField(file.Comments());
    }

    if (dateEditParam->IsSpecified())
    {
        file.SetDateDumped(dateEditParam->Value());
        PrintField(file.DateDumped());
    }

    if (songLengthEditParam->IsSpecified())
    {
        file.SetSongLength(songLengthEditParam->Value());
        PrintField(file.SongLength());
    }

    if (fadeLengthEditParam->IsSpecified())
    {
        file.SetFadeLength(fadeLengthEditParam->Value());
        PrintField(file.FadeLength());
    }

    if (artistEditParam->IsSpecified())
    {
        file.SetSongArtist(artistEditParam->Value());
        PrintField(file.SongArtist());
    }

    if (channelEditParam->IsSpecified())
    {
        file.SetDefaultChannelState(channelEditParam->Value());
        PrintField(file.DefaultChannelState());
    }

    if (emulatorEditParam->IsSpecified())
    {
        file.SetEmulatorUsed(emulatorEditParam->Value());
        PrintField(file.EmulatorUsed());
    }

    if (titleEditParam->IsSpecified())
    {
        file.SetOstTitle(titleEditParam->Value());
        PrintField(file.OstTitle());
    }

    if (discEditParam->IsSpecified())
    {
        file.SetOstDisc(discEditParam->Value());
        PrintField(file.OstDisc());
    }

    if (trackEditParam->IsSpecified())
    {
        file.SetOstTrack(trackEditParam->Value());
        PrintField(file.OstTrack());
    }

    if (publisherEditParam->IsSpecified())
    {
        file.SetPublisherName(publisherEditParam->Value());
        PrintField(file.PublisherName());
    }

    if (copyrightEditParam->IsSpecified())
    {
        file.SetCopyrightYear(copyrightEditParam->Value());
        PrintField(file.CopyrightYear());
    }

    if (introLengthEditParam->IsSpecified())
    {
        file.SetIntroLength(introLengthEditParam->Value());
        PrintField(file.IntroLength());
    }

    if (loopLengthEditParam->IsSpecified())
    {
        file.SetLoopLength(loopLengthEditParam->Value());
        PrintField(file.LoopLength());
    }

    if (endLengthEditParam->IsSpecified())
    {
        file.SetEndLength(endLengthEditParam->Value());
        PrintField(file.EndLength());
    }

    if (mutedEditParam->IsSpecified())
    {
        file.SetMutedVoices(mutedEditParam->Value());
        PrintField(file.MutedVoices());
    }

    if (loopTimesEditParam->IsSpecified())
    {
        file.SetLoopTimes(loopTimesEditParam->Value());
        PrintField(file.LoopTimes());
    }

    if (preampEditParam->IsSpecified())
    {
        file.SetPreampLevel(preampEditParam->Value());
        PrintField(file.PreampLevel());
    }
        
    file.Save();

    std::cout << std::endl;
        
    return 0;
}

int Program::IncrementTrack(Spc::File& file)
{
    uint8_t track = file.OstTrack().Value();
    int incrementAmount = std::stoi(incrementOption->Values()[0]);
    track += incrementAmount;
    file.SetOstTrack(std::to_string(track));
    file.Save();
    return 0;
}

int Program::Run(std::vector<std::string> arguments)
{
    DefineParameters();
    InitializeParser(arguments);
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