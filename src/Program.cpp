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
    std::cout << "ID666Edit v0.4" << std::endl;
    std::cout << "Copyright (C) 2025 Stephen Bonar" << std::endl << std::endl;
}

void Program::DefineCmdLineParameters()
{
    CmdLine::ProgParam::Definition progDef;
    progDef.name = "id666edit";
    progDef.description = "An ID666 metadata tag editor for .SPC files";
    progParam = std::make_unique<CmdLine::ProgParam>(progDef);

    CmdLine::PosParam::Definition fileDef;
    fileDef.name = "spcfile";
    fileDef.description = "The .spc file to open";
    fileDef.isMandatory = true;
    spcFileParam = std::make_unique<CmdLine::PosParam>(fileDef);

    CmdLine::ValueOption::Definition printDef;
    printDef.shortName = 'p';
    printDef.longName = "print";
    printDef.description = "Prints the specified item in the .spc file";
    printOption = std::make_unique<CmdLine::ValueOption>(printDef);

    CmdLine::ValueOption::Definition editDef;
    editDef.shortName = 'e';
    editDef.longName = "edit";
    editDef.description = "Edits the specified tag item (use \"name=value\")";
    editOption = std::make_unique<CmdLine::ValueOption>(editDef);

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

    CmdLine::OptionParam::Definition channelDef;
    channelDef.name = "channel";
    channelDef.description = "Default channel disables (purpose unknown)";
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
    editOption->Add(publisherPrintParam.get());

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

void Program::InitializeCmdLineParser(std::vector<std::string> arguments)
{
    parser = std::make_unique<CmdLine::Parser>(progParam.get(), arguments);
    parser->Add(spcFileParam.get());
    parser->Add(printOption.get());
    parser->Add(editOption.get());
}

int Program::SelectMode()
{
    if (spcFileParam->IsSpecified())
    {
        SpcFile file{ spcFileParam->Value() };
        
        if (!file.Load())
        {
            std::cerr << "ERROR: unable to open file." << std::endl;
            return 2;
        }

        if (printOption->IsSpecified())
            return PrintSpecifiedItems(file);

        if (editOption->IsSpecified())
            return EditSpecifiedItems(file);

        return PrintSpcFile(file);
    }
    else if (parser->BuiltInHelpOptionIsSpecified())
    {
        std::cout << parser->GenerateHelp();
        return 0;
    }
    else
    {
        std::cerr << parser->GenerateUsage();
        return 1;
    }
}

void Program::PrintSectionHeader(std::string title)
{
    std::cout << title << std::endl;
    std::cout << "-----------------------------------------------------------";
    std::cout << "--------------------" << std::endl;
}

void Program::PrintField(SpcField* field)
{
    std::cout << FormatField(field) << std::endl;
}

void Program::PrintField(SpcTextField field)
{
    PrintField(&field);
}

void Program::PrintField(SpcDateField field)
{
    PrintField(&field);
}

void Program::PrintField(SpcNumericField field)
{
    PrintField(&field);
}

void Program::PrintField(SpcTrackField field)
{
    PrintField(&field);
}

void Program::PrintField(SpcEmulatorField field)
{
    PrintField(&field);
}

void Program::PrintField(SpcBinaryField field)
{
    PrintField(&field);
}

int Program::PrintSpcFile(SpcFile& file)
{
    PrintHeader(file);
    PrintTag(file);
    std::cout << std::endl;
    return 0;
}

void Program::PrintHeader(SpcFile& file)
{
    SpcHeader header = file.Header();
    PrintSectionHeader("SPC File Header");
    std::cout << header.ToString() << std::endl;
}

void Program::PrintTag(SpcFile& file)
{
    PrintSectionHeader("ID666 Tag");

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
}

void Program::PrintTextTag(SpcFile& file)
{
    std::cout << FormatValue("Tag Type", "Text") << std::endl;
    ID666TextTag tag = file.TextTag();
    std::cout << tag.ToString() << std::endl;
}

void Program::PrintBinaryTag(SpcFile& file)
{
    std::cout << FormatValue("Tag Type", "Binary") << std::endl;
    ID666BinaryTag tag = file.BinaryTag();
    std::cout << tag.ToString() << std::endl;
}

void Program::PrintExtendedTag(SpcFile& file)
{
    PrintSectionHeader("Extended ID666 Tag");
    std::cout << FormatValue("Has Extended Tag", "True") << std::endl;
    Binary::ChunkHeader extendedTagHeader = file.ExtendedTagHeader();
    ID666ExtendedTag tag = file.ExtendedTag();
    std::cout << FormatValue("IFF Chunk ID", extendedTagHeader.id.ToString());
    std::cout << std::endl;
    std::cout << FormatValue("IFF Chunk Size", extendedTagHeader.dataSize.ToString());
    std::cout << std::endl;
    std::cout << tag.ToString() << std::endl;
}

int Program::PrintSpecifiedItems(SpcFile& file)
{
    if (headerPrintParam->IsSpecified())
        PrintHeader(file);

    if (tagPrintParam->IsSpecified())
        PrintTag(file);

    if (songPrintParam->IsSpecified())
        PrintField(file.SongTitle());
        //std::cout << FormatField(&file.SongTitle()) << std::endl;

    if (gamePrintParam->IsSpecified())
        PrintField(file.GameTitle());
        //std::cout << FormatField(&file.GameTitle()) << std::endl;

    if (dumperPrintParam->IsSpecified())
        PrintField(file.DumperName());
        //std::cout << FormatField(&file.DumperName()) << std::endl;

    if (commentsPrintParam->IsSpecified())
        PrintField(file.Comments());
        //std::cout << FormatField(&file.Comments()) << std::endl;
    
    if (datePrintParam->IsSpecified())
        PrintField(file.DateDumped());
        //std::cout << FormatField(&file.DateDumped()) << std::endl;

    if (songLengthPrintParam->IsSpecified())
        PrintField(file.SongLength());
        //std::cout << FormatField(&file.SongLength()) << std::endl;

    if (fadeLengthPrintParam->IsSpecified())
        PrintField(file.FadeLength());
        //std::cout << FormatField(&file.FadeLength()) << std::endl;

    if (artistPrintParam->IsSpecified())
        PrintField(file.SongArtist());
        //std::cout << FormatField(&file.SongArtist()) << std::endl;

    if (channelPrintParam->IsSpecified())
        PrintField(file.DefaultChannelDisables());
        //std::cout << FormatField(&file.DefaultChannelDisables()) << std::endl;

    if (emulatorPrintParam->IsSpecified())
        PrintField(file.EmulatorUsed());
        //std::cout << FormatField(&file.EmulatorUsed()) << std::endl;

    if (titlePrintParam->IsSpecified())
        PrintField(file.OstTitle());
        //std::cout << FormatField(&file.OstTitle()) << std::endl;

    if (discPrintParam->IsSpecified())
        PrintField(file.OstDisc());
        //std::cout << FormatField(&file.OstDisc()) << std::endl;

    if (trackPrintParam->IsSpecified())
        PrintField(file.OstTrack());
        //std::cout << FormatField(&file.OstTrack()) << std::endl;

    if (publisherPrintParam->IsSpecified())
        PrintField(file.PublisherName());
        //std::cout << FormatField(&file.PublisherName()) << std::endl;

    if (copyrightPrintParam->IsSpecified())
        PrintField(file.CopyrightYear());
        //std::cout << FormatField(&file.CopyrightYear()) << std::endl;

    if (introLengthPrintParam->IsSpecified())
        PrintField(file.IntroLength());
        //std::cout << FormatField(&file.IntroLength()) << std::endl;

    if (loopLengthPrintParam->IsSpecified())
        PrintField(file.LoopLength());
        //std::cout << FormatField(&file.LoopLength()) << std::endl;

    if (endLengthPrintParam->IsSpecified())
        PrintField(file.EndLength());
        //std::cout << FormatField(&file.EndLength()) << std::endl;

    if (mutedPrintParam->IsSpecified())
        PrintField(file.MutedVoices());
        //std::cout << FormatField(&file.MutedVoices()) << std::endl;

    if (loopTimesPrintParam->IsSpecified())
        PrintField(file.LoopTimes());
        //std::cout << FormatField(&file.LoopTimes()) << std::endl;

    if (preampPrintParam->IsSpecified())
        PrintField(file.PreampLevel());
        //std::cout << FormatField(&file.PreampLevel()) << std::endl;

    return 0;
}

int Program::EditSpecifiedItems(SpcFile& file)
{
    if (songEditParam->IsSpecified())
        file.SetSongTitle(songEditParam->Value());

    if (gameEditParam->IsSpecified())
        file.SetGameTitle(gameEditParam->Value());

    if (dumperEditParam->IsSpecified())
        file.SetDumperName(dumperEditParam->Value());

    if (commentsEditParam->IsSpecified())
        file.SetComments(commentsEditParam->Value());

    if (dateEditParam->IsSpecified())
        file.SetDateDumped(dateEditParam->Value());

    file.Save();
        
    return 0;
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