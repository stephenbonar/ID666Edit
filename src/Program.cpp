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
    std::cout << "ID666Edit v0.3" << std::endl;
    std::cout << "Copyright (C) 2025 Stephen Bonar" << std::endl << std::endl;
}

void Program::DefineCmdLineParameters()
{
    CmdLine::ProgParam::Definition progDef;
    progDef.name = "ID666Edit";
    progDef.description = "An ID666 metadata tag editor for .SPC files";
    progParam = std::make_unique<CmdLine::ProgParam>(progDef);

    CmdLine::PosParam::Definition fileDef;
    fileDef.name = "spc_file";
    fileDef.description = "The .spc file to open";
    fileDef.isMandatory = true;
    spcFileParam = std::make_unique<CmdLine::PosParam>(fileDef);

    CmdLine::ValueOption::Definition printDef;
    printDef.shortName = 'p';
    printDef.longName = "print";
    printDef.description = "Prints the specified item in the .spc file";
    printOption = std::make_unique<CmdLine::ValueOption>(printDef);

    CmdLine::OptionParam::Definition tagPrintDef;
    tagPrintDef.name = "tag";
    tagPrintDef.description = "Prints the entire ID666 tag";
    tagPrintParam = std::make_unique<CmdLine::OptionParam>(tagPrintDef);
    printOption->Add(tagPrintParam.get());

    CmdLine::OptionParam::Definition headerPrintDef;
    headerPrintDef.name = "header";
    headerPrintDef.description = "Prints the .spc file header";
    headerPrintParam = std::make_unique<CmdLine::OptionParam>(headerPrintDef);
    printOption->Add(headerPrintParam.get());

    CmdLine::OptionParam::Definition songPrintDef;
    songPrintDef.name = "song";
    songPrintDef.description = "Prints the song name from the tags";
    songPrintParam = std::make_unique<CmdLine::OptionParam>(songPrintDef);
    printOption->Add(songPrintParam.get());

    CmdLine::OptionParam::Definition gamePrintDef;
    gamePrintDef.name = "game";
    gamePrintDef.description = "Prints the game name from the tags";
    gamePrintParam = std::make_unique<CmdLine::OptionParam>(gamePrintDef);
    printOption->Add(gamePrintParam.get());

    CmdLine::OptionParam::Definition dumperPrintDef;
    dumperPrintDef.name = "dumper";
    dumperPrintDef.description = "Prints the dumper from the tags";
    dumperPrintParam = std::make_unique<CmdLine::OptionParam>(dumperPrintDef);
    printOption->Add(dumperPrintParam.get());

    CmdLine::OptionParam::Definition commentsPrintDef;
    commentsPrintDef.name = "comments";
    commentsPrintDef.description = "Prints the comments from the tags";
    commentsPrintParam = std::make_unique<CmdLine::OptionParam>(
        commentsPrintDef);
    printOption->Add(commentsPrintParam.get());

    CmdLine::OptionParam::Definition datePrintDef;
    datePrintDef.name = "date";
    datePrintDef.description = "Prints the date dumped from the tags";
    datePrintParam = std::make_unique<CmdLine::OptionParam>(datePrintDef);
    printOption->Add(datePrintParam.get());

    CmdLine::OptionParam::Definition songLengthPrintDef;
    songLengthPrintDef.name = "songlength";
    songLengthPrintDef.description = "Prints the song length from the tags";
    songLengthPrintParam = std::make_unique<CmdLine::OptionParam>(
        songLengthPrintDef);
    printOption->Add(songLengthPrintParam.get());

    CmdLine::OptionParam::Definition fadeLengthPrintDef;
    fadeLengthPrintDef.name = "fadelength";
    fadeLengthPrintDef.description = "Prints the fade length from the tags";
    fadeLengthPrintParam = std::make_unique<CmdLine::OptionParam>(
        fadeLengthPrintDef);
    printOption->Add(fadeLengthPrintParam.get());

    CmdLine::OptionParam::Definition artistPrintDef;
    artistPrintDef.name = "artist";
    artistPrintDef.description = "Prints the song artist from the tags";
    artistPrintParam = std::make_unique<CmdLine::OptionParam>(artistPrintDef);
    printOption->Add(artistPrintParam.get());

    CmdLine::OptionParam::Definition channelPrintDef;
    channelPrintDef.name = "channel";
    channelPrintDef.description = "Prints the channel disables from the tags";
    channelPrintParam = std::make_unique<CmdLine::OptionParam>(
        channelPrintDef);
    printOption->Add(channelPrintParam.get());

    CmdLine::OptionParam::Definition emulatorPrintDef;
    emulatorPrintDef.name = "emulator";
    emulatorPrintDef.description = "Prints the emulator used from the tags";
    emulatorPrintParam = std::make_unique<CmdLine::OptionParam>(
        emulatorPrintDef);
    printOption->Add(emulatorPrintParam.get());

    CmdLine::OptionParam::Definition titlePrintDef;
    titlePrintDef.name = "title";
    titlePrintDef.description = "Prints the OST title from the tags";
    titlePrintParam = std::make_unique<CmdLine::OptionParam>(titlePrintDef);
    printOption->Add(titlePrintParam.get());

    CmdLine::OptionParam::Definition discPrintDef;
    discPrintDef.name = "disc";
    discPrintDef.description = "Prints the OST disc from the tags";
    discPrintParam = std::make_unique<CmdLine::OptionParam>(discPrintDef);
    printOption->Add(discPrintParam.get());

    CmdLine::OptionParam::Definition trackPrintDef;
    trackPrintDef.name = "track";
    trackPrintDef.description = "Prints the OST track from the tags";
    trackPrintParam = std::make_unique<CmdLine::OptionParam>(trackPrintDef);
    printOption->Add(trackPrintParam.get());

    CmdLine::OptionParam::Definition publisherPrintDef;
    publisherPrintDef.name = "publisher";
    publisherPrintDef.description = "Prints the publisher from the tags";
    publisherPrintParam = std::make_unique<CmdLine::OptionParam>(publisherPrintDef);
    printOption->Add(publisherPrintParam.get());

    CmdLine::OptionParam::Definition copyrightPrintDef;
    copyrightPrintDef.name = "copyright";
    copyrightPrintDef.description = "Prints the copyright from the tags";
    copyrightPrintParam = std::make_unique<CmdLine::OptionParam>(copyrightPrintDef);
    printOption->Add(copyrightPrintParam.get());

    CmdLine::OptionParam::Definition introLengthPrintDef;
    introLengthPrintDef.name = "introlength";
    introLengthPrintDef.description = "Prints the intro length from the tags";
    introLengthPrintParam = std::make_unique<CmdLine::OptionParam>(
        introLengthPrintDef);
    printOption->Add(introLengthPrintParam.get());

    CmdLine::OptionParam::Definition loopLengthPrintDef;
    loopLengthPrintDef.name = "looplength";
    loopLengthPrintDef.description = "Prints the loop length from the tags";
    loopLengthPrintParam = std::make_unique<CmdLine::OptionParam>(
        loopLengthPrintDef);
    printOption->Add(loopLengthPrintParam.get());

    CmdLine::OptionParam::Definition endLengthPrintDef;
    endLengthPrintDef.name = "endlength";
    endLengthPrintDef.description = "Prints the end length from the tags";
    endLengthPrintParam = std::make_unique<CmdLine::OptionParam>(
        endLengthPrintDef);
    printOption->Add(endLengthPrintParam.get());

    CmdLine::OptionParam::Definition mutedPrintDef;
    mutedPrintDef.name = "muted";
    mutedPrintDef.description = "Prints the muted voices from the tags";
    mutedPrintParam = std::make_unique<CmdLine::OptionParam>(
        mutedPrintDef);
    printOption->Add(mutedPrintParam.get());

    CmdLine::OptionParam::Definition loopTimesPrintDef;
    loopTimesPrintDef.name = "looptimes";
    loopTimesPrintDef.description = "Prints the loop times from the tags";
    loopTimesPrintParam = std::make_unique<CmdLine::OptionParam>(
        loopTimesPrintDef);
    printOption->Add(loopTimesPrintParam.get());

    CmdLine::OptionParam::Definition preampPrintDef;
    preampPrintDef.name = "preamp";
    preampPrintDef.description = "Prints the preamp level from the tags";
    preampPrintParam = std::make_unique<CmdLine::OptionParam>(
        preampPrintDef);
    printOption->Add(preampPrintParam.get());
}

void Program::InitializeCmdLineParser(std::vector<std::string> arguments)
{
    parser = std::make_unique<CmdLine::Parser>(progParam.get(), arguments);
    parser->Add(spcFileParam.get());
    parser->Add(printOption.get());
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
        {
            return PrintSpecifiedItems(file);
        }
        else
        {
            return PrintSpcFile(file);
        }
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
    std::cout << header.ToString() << std::endl;
}

void Program::PrintTag(SpcFile& file)
{
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
    std::cout << std::endl;

    ID666TextTag tag = file.TextTag();
    std::cout << tag.ToString() << std::endl;
}

void Program::PrintBinaryTag(SpcFile& file)
{
    std::cout << FormatValue("Tag Type", "Binary") << std::endl;
    std::cout << std::endl;

    ID666BinaryTag tag = file.BinaryTag();
    std::cout << tag.ToString() << std::endl;
}

void Program::PrintExtendedTag(SpcFile& file)
{
    std::cout << FormatValue("Has Extended Tag", "True") << std::endl;
    ID666ExtendedTag tag = file.ExtendedTag();
    std::cout << tag.ToString() << std::endl;
}

int Program::PrintSpecifiedItems(SpcFile& file)
{
    if (headerPrintParam->IsSpecified())
        PrintHeader(file);

    if (tagPrintParam->IsSpecified())
        PrintTag(file);

    if (songPrintParam->IsSpecified())
        std::cout << FormatField(&file.SongTitle()) << std::endl;

    if (gamePrintParam->IsSpecified())
        std::cout << FormatField(&file.GameTitle()) << std::endl;

    if (dumperPrintParam->IsSpecified())
        std::cout << FormatField(&file.DumperName()) << std::endl;

    if (commentsPrintParam->IsSpecified())
        std::cout << FormatField(&file.Comments()) << std::endl;
    
    if (datePrintParam->IsSpecified())
        std::cout << FormatField(&file.DateDumped()) << std::endl;

    if (songLengthPrintParam->IsSpecified())
        std::cout << FormatField(&file.SongLength()) << std::endl;

    if (fadeLengthPrintParam->IsSpecified())
        std::cout << FormatField(&file.FadeLength()) << std::endl;

    if (artistPrintParam->IsSpecified())
        std::cout << FormatField(&file.SongArtist()) << std::endl;

    if (channelPrintParam->IsSpecified())
        std::cout << FormatField(&file.DefaultChannelDisables()) << std::endl;

    if (emulatorPrintParam->IsSpecified())
        std::cout << FormatField(&file.EmulatorUsed()) << std::endl;

    if (titlePrintParam->IsSpecified())
        std::cout << FormatField(&file.OstTitle()) << std::endl;

    if (discPrintParam->IsSpecified())
        std::cout << FormatField(&file.OstDisc()) << std::endl;

    if (trackPrintParam->IsSpecified())
        std::cout << FormatField(&file.OstTrack()) << std::endl;

    if (publisherPrintParam->IsSpecified())
        std::cout << FormatField(&file.PublisherName()) << std::endl;

    if (copyrightPrintParam->IsSpecified())
        std::cout << FormatField(&file.CopyrightYear()) << std::endl;

    if (introLengthPrintParam->IsSpecified())
        std::cout << FormatField(&file.IntroLength()) << std::endl;

    if (loopLengthPrintParam->IsSpecified())
        std::cout << FormatField(&file.LoopLength()) << std::endl;

    if (endLengthPrintParam->IsSpecified())
        std::cout << FormatField(&file.EndLength()) << std::endl;

    if (mutedPrintParam->IsSpecified())
        std::cout << FormatField(&file.MutedVoices()) << std::endl;

    if (loopTimesPrintParam->IsSpecified())
        std::cout << FormatField(&file.LoopTimes()) << std::endl;

    if (preampPrintParam->IsSpecified())
        std::cout << FormatField(&file.PreampLevel()) << std::endl;

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