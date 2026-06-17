// Program.cpp - Defines the Program class.
//
// Copyright (C) 2026 Stephen Bonar
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
    std::cout << "ID666Edit v1.0 Alpha" << std::endl;
    std::cout << "Copyright (C) 2026 Stephen Bonar" << std::endl << std::endl;
}

void Program::DefinePosParams()
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
}

void Program::DefineOptions()
{
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

    CmdLine::ValueOption::Definition whereDef;
    whereDef.shortName = 'w';
    whereDef.longName = "where";
    whereDef.description = 
        "Filter on matching parameter values (use \"name=value\")";
    whereOption = std::make_unique<CmdLine::ValueOption>(whereDef);

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
}

void Program::DefineOptionParams()
{
    CmdLine::OptionParam::Definition idDef;
    idDef.name = "id";
    idDef.description = "The file header ID of the .spc file";
    idPrintParam = std::make_unique<CmdLine::OptionParam>(idDef);
    idWhereParam = std::make_unique<CmdLine::OptionParam>(idDef);
    printOption->Add(idPrintParam.get());
    whereOption->Add(idWhereParam.get());

    CmdLine::OptionParam::Definition hasTagDef;
    hasTagDef.name = "hastag";
    hasTagDef.description = "Whether the file has an ID666 tag";
    hasTagPrintParam = std::make_unique<CmdLine::OptionParam>(hasTagDef);
    hasTagWhereParam = std::make_unique<CmdLine::OptionParam>(hasTagDef);
    printOption->Add(hasTagPrintParam.get());
    whereOption->Add(hasTagWhereParam.get());

    CmdLine::OptionParam::Definition tagDef;
    tagDef.name = "tag";
    tagDef.description = "The entire ID666 tag";
    tagPrintParam = std::make_unique<CmdLine::OptionParam>(tagDef);
    tagWhereParam = std::make_unique<CmdLine::OptionParam>(tagDef);
    printOption->Add(tagPrintParam.get());
    whereOption->Add(tagWhereParam.get());

    CmdLine::OptionParam::Definition headerDef;
    headerDef.name = "header";
    headerDef.description = "The .spc file header";
    headerPrintParam = std::make_unique<CmdLine::OptionParam>(headerDef);
    headerWhereParam = std::make_unique<CmdLine::OptionParam>(headerDef);
    printOption->Add(headerPrintParam.get());
    whereOption->Add(headerWhereParam.get());

    CmdLine::OptionParam::Definition tagTypeDef;
    tagTypeDef.name = "tagtype";
    tagTypeDef.description = "The type of the ID666 tag";
    tagTypePrintParam = std::make_unique<CmdLine::OptionParam>(tagTypeDef);
    tagTypeWhereParam = std::make_unique<CmdLine::OptionParam>(tagTypeDef);
    printOption->Add(tagTypePrintParam.get());
    whereOption->Add(tagTypeWhereParam.get());

    CmdLine::OptionParam::Definition hasExtendedDef;
    hasExtendedDef.name = "hasextended";
    hasExtendedDef.description = "Whether the tag has extended fields";
    hasExtendedPrintParam = std::make_unique<CmdLine::OptionParam>(
        hasExtendedDef);
    hasExtendedWhereParam = std::make_unique<CmdLine::OptionParam>(
        hasExtendedDef);
    printOption->Add(hasExtendedPrintParam.get());
    whereOption->Add(hasExtendedWhereParam.get());

    CmdLine::OptionParam::Definition songDef;
    songDef.name = "song";
    songDef.description = "The name of the song";
    songPrintParam = std::make_unique<CmdLine::OptionParam>(songDef);
    songEditParam = std::make_unique<CmdLine::OptionParam>(songDef);
    songWhereParam = std::make_unique<CmdLine::OptionParam>(songDef);
    printOption->Add(songPrintParam.get());
    editOption->Add(songEditParam.get());
    whereOption->Add(songWhereParam.get());

    CmdLine::OptionParam::Definition gameDef;
    gameDef.name = "game";
    gameDef.description = "The name of the game";
    gamePrintParam = std::make_unique<CmdLine::OptionParam>(gameDef);
    gameEditParam = std::make_unique<CmdLine::OptionParam>(gameDef);
    gameWhereParam = std::make_unique<CmdLine::OptionParam>(gameDef);
    printOption->Add(gamePrintParam.get());
    editOption->Add(gameEditParam.get());
    whereOption->Add(gameWhereParam.get());

    CmdLine::OptionParam::Definition dumperDef;
    dumperDef.name = "dumper";
    dumperDef.description = "The name of the person who dumped the song";
    dumperPrintParam = std::make_unique<CmdLine::OptionParam>(dumperDef);
    dumperEditParam = std::make_unique<CmdLine::OptionParam>(dumperDef);
    dumperWhereParam = std::make_unique<CmdLine::OptionParam>(dumperDef);
    printOption->Add(dumperPrintParam.get());
    editOption->Add(dumperEditParam.get());
    whereOption->Add(dumperWhereParam.get());

    CmdLine::OptionParam::Definition commentsDef;
    commentsDef.name = "comments";
    commentsDef.description = "The tagger's comments";
    commentsPrintParam = std::make_unique<CmdLine::OptionParam>(commentsDef);
    commentsEditParam = std::make_unique<CmdLine::OptionParam>(commentsDef);
    commentsWhereParam = std::make_unique<CmdLine::OptionParam>(commentsDef);
    printOption->Add(commentsPrintParam.get());
    editOption->Add(commentsEditParam.get());
    whereOption->Add(commentsWhereParam.get());

    CmdLine::OptionParam::Definition dateDef;
    dateDef.name = "date";
    dateDef.description = "The date the song was dumped";
    datePrintParam = std::make_unique<CmdLine::OptionParam>(dateDef);
    dateEditParam = std::make_unique<CmdLine::OptionParam>(dateDef);
    dateWhereParam = std::make_unique<CmdLine::OptionParam>(dateDef);
    printOption->Add(datePrintParam.get());
    editOption->Add(dateEditParam.get());
    whereOption->Add(dateWhereParam.get());

    CmdLine::OptionParam::Definition songLengthDef;
    songLengthDef.name = "songlength";
    songLengthDef.description = "The length of the song, in seconds";
    songLengthPrintParam = std::make_unique<CmdLine::OptionParam>(
        songLengthDef);
    songLengthEditParam = std::make_unique<CmdLine::OptionParam>(
        songLengthDef);
    songLengthWhereParam = std::make_unique<CmdLine::OptionParam>(
        songLengthDef);
    printOption->Add(songLengthPrintParam.get());
    editOption->Add(songLengthEditParam.get());
    whereOption->Add(songLengthWhereParam.get());

    CmdLine::OptionParam::Definition fadeLengthDef;
    fadeLengthDef.name = "fadelength";
    fadeLengthDef.description = "The length of fade out, in milliseconds";
    fadeLengthPrintParam = std::make_unique<CmdLine::OptionParam>(
        fadeLengthDef);
    fadeLengthEditParam = std::make_unique<CmdLine::OptionParam>(
        fadeLengthDef);
    fadeLengthWhereParam = std::make_unique<CmdLine::OptionParam>(
        fadeLengthDef);
    printOption->Add(fadeLengthPrintParam.get());
    editOption->Add(fadeLengthEditParam.get());
    whereOption->Add(fadeLengthWhereParam.get());

    CmdLine::OptionParam::Definition artistDef;
    artistDef.name = "artist";
    artistDef.description = "The song artist / composer";
    artistPrintParam = std::make_unique<CmdLine::OptionParam>(artistDef);
    artistEditParam = std::make_unique<CmdLine::OptionParam>(artistDef);
    artistWhereParam = std::make_unique<CmdLine::OptionParam>(artistDef);
    printOption->Add(artistPrintParam.get());
    editOption->Add(artistEditParam.get());
    whereOption->Add(artistWhereParam.get());

    CmdLine::OptionParam::Definition channelDef;
    channelDef.name = "channels";
    channelDef.description = 
        "Default disabled channels (0 = enabled, 1 = disabled)";
    channelPrintParam = std::make_unique<CmdLine::OptionParam>(channelDef);
    channelEditParam = std::make_unique<CmdLine::OptionParam>(channelDef);
    channelWhereParam = std::make_unique<CmdLine::OptionParam>(channelDef);
    printOption->Add(channelPrintParam.get());
    editOption->Add(channelEditParam.get());
    whereOption->Add(channelWhereParam.get());

    CmdLine::OptionParam::Definition emulatorDef;
    emulatorDef.name = "emulator";
    emulatorDef.description = "The emulator used to dump the song";
    emulatorPrintParam = std::make_unique<CmdLine::OptionParam>(emulatorDef);
    emulatorEditParam = std::make_unique<CmdLine::OptionParam>(emulatorDef);
    emulatorWhereParam = std::make_unique<CmdLine::OptionParam>(emulatorDef);
    printOption->Add(emulatorPrintParam.get());
    editOption->Add(emulatorEditParam.get());
    whereOption->Add(emulatorWhereParam.get());

    CmdLine::OptionParam::Definition titleDef;
    titleDef.name = "title";
    titleDef.description = "The Original Sound Track (OST) album title";
    titlePrintParam = std::make_unique<CmdLine::OptionParam>(titleDef);
    titleEditParam = std::make_unique<CmdLine::OptionParam>(titleDef);
    titleWhereParam = std::make_unique<CmdLine::OptionParam>(titleDef);
    printOption->Add(titlePrintParam.get());
    editOption->Add(titleEditParam.get());
    whereOption->Add(titleWhereParam.get());

    CmdLine::OptionParam::Definition discDef;
    discDef.name = "disc";
    discDef.description = "The Original Sound Track (OST) disc number";
    discPrintParam = std::make_unique<CmdLine::OptionParam>(discDef);
    discEditParam = std::make_unique<CmdLine::OptionParam>(discDef);
    discWhereParam = std::make_unique<CmdLine::OptionParam>(discDef);
    printOption->Add(discPrintParam.get());
    editOption->Add(discEditParam.get());
    whereOption->Add(discWhereParam.get());

    CmdLine::OptionParam::Definition trackDef;
    trackDef.name = "track";
    trackDef.description = "The Original Sound Track (OST) from the tags";
    trackPrintParam = std::make_unique<CmdLine::OptionParam>(trackDef);
    trackEditParam = std::make_unique<CmdLine::OptionParam>(trackDef);
    trackWhereParam = std::make_unique<CmdLine::OptionParam>(trackDef);
    printOption->Add(trackPrintParam.get());
    editOption->Add(trackEditParam.get());
    whereOption->Add(trackWhereParam.get());

    CmdLine::OptionParam::Definition publisherDef;
    publisherDef.name = "publisher";
    publisherDef.description = "The publisher of the game";
    publisherPrintParam = std::make_unique<CmdLine::OptionParam>(publisherDef);
    publisherEditParam = std::make_unique<CmdLine::OptionParam>(publisherDef);
    publisherWhereParam = std::make_unique<CmdLine::OptionParam>(publisherDef);
    printOption->Add(publisherPrintParam.get());
    editOption->Add(publisherEditParam.get());
    whereOption->Add(publisherWhereParam.get());

    CmdLine::OptionParam::Definition copyrightDef;
    copyrightDef.name = "copyright";
    copyrightDef.description = "The year the game was copyrighted";
    copyrightPrintParam = std::make_unique<CmdLine::OptionParam>(copyrightDef);
    copyrightEditParam = std::make_unique<CmdLine::OptionParam>(copyrightDef);
    copyrightWhereParam = std::make_unique<CmdLine::OptionParam>(copyrightDef);
    printOption->Add(copyrightPrintParam.get());
    editOption->Add(copyrightEditParam.get());
    whereOption->Add(copyrightWhereParam.get());

    CmdLine::OptionParam::Definition introLengthDef;
    introLengthDef.name = "introlength";
    introLengthDef.description = "The length of the song intro, in ticks";
    introLengthPrintParam = std::make_unique<CmdLine::OptionParam>(
        introLengthDef);
    introLengthEditParam = std::make_unique<CmdLine::OptionParam>(
        introLengthDef);
    introLengthWhereParam = std::make_unique<CmdLine::OptionParam>(
        introLengthDef);
    printOption->Add(introLengthPrintParam.get());
    editOption->Add(introLengthEditParam.get());
    whereOption->Add(introLengthWhereParam.get());

    CmdLine::OptionParam::Definition loopLengthDef;
    loopLengthDef.name = "looplength";
    loopLengthDef.description = "The length of each song loop, in ticks";
    loopLengthPrintParam = std::make_unique<CmdLine::OptionParam>(
        loopLengthDef);
    loopLengthEditParam = std::make_unique<CmdLine::OptionParam>(
        loopLengthDef);
    loopLengthWhereParam = std::make_unique<CmdLine::OptionParam>(
        loopLengthDef);
    printOption->Add(loopLengthPrintParam.get());
    editOption->Add(loopLengthEditParam.get());
    whereOption->Add(loopLengthWhereParam.get());

    CmdLine::OptionParam::Definition endLengthDef;
    endLengthDef.name = "endlength";
    endLengthDef.description = "The length of the end of the song, in ticks";
    endLengthPrintParam = std::make_unique<CmdLine::OptionParam>(endLengthDef);
    endLengthEditParam = std::make_unique<CmdLine::OptionParam>(endLengthDef);
    endLengthWhereParam = std::make_unique<CmdLine::OptionParam>(endLengthDef);
    printOption->Add(endLengthPrintParam.get());
    editOption->Add(endLengthEditParam.get());
    whereOption->Add(endLengthWhereParam.get());

    CmdLine::OptionParam::Definition mutedDef;
    mutedDef.name = "muted";
    mutedDef.description = "8-bit value where each set bit mutes a voice";
    mutedPrintParam = std::make_unique<CmdLine::OptionParam>(mutedDef);
    mutedEditParam = std::make_unique<CmdLine::OptionParam>(mutedDef);
    mutedWhereParam = std::make_unique<CmdLine::OptionParam>(mutedDef);
    printOption->Add(mutedPrintParam.get());
    editOption->Add(mutedEditParam.get());
    whereOption->Add(mutedWhereParam.get());

    CmdLine::OptionParam::Definition loopTimesDef;
    loopTimesDef.name = "looptimes";
    loopTimesDef.description = "The number of times the song should loop";
    loopTimesPrintParam = std::make_unique<CmdLine::OptionParam>(loopTimesDef);
    loopTimesEditParam = std::make_unique<CmdLine::OptionParam>(loopTimesDef);
    loopTimesWhereParam = std::make_unique<CmdLine::OptionParam>(loopTimesDef);
    printOption->Add(loopTimesPrintParam.get());
    editOption->Add(loopTimesEditParam.get());
    whereOption->Add(loopTimesWhereParam.get());

    CmdLine::OptionParam::Definition preampDef;
    preampDef.name = "preamp";
    preampDef.description = "The preamp level to apply";
    preampPrintParam = std::make_unique<CmdLine::OptionParam>(preampDef);
    preampEditParam = std::make_unique<CmdLine::OptionParam>(preampDef);
    preampWhereParam = std::make_unique<CmdLine::OptionParam>(preampDef);
    printOption->Add(preampPrintParam.get());
    editOption->Add(preampEditParam.get());
    whereOption->Add(preampWhereParam.get());
}

void Program::DefineParams()
{
    DefinePosParams();
    DefineOptions();
    DefineOptionParams();
}

void Program::InitializeParser(std::vector<std::string> arguments)
{
    parser = std::make_unique<CmdLine::Parser>(progParam.get(), arguments);
    parser->Set(spcFileParam.get());
    parser->Add(printOption.get());
    parser->Add(editOption.get());
    parser->Add(whereOption.get());
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
        const std::vector<std::string> spcFiles = spcFileParam->Values();

        for (const std::string& filePath : spcFiles)
        {
                
            int result = ProcessSpcFile(filePath);

            if (result != 0)
            {
                return result;
            }
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

bool Program::MatchWhereParam(CmdLine::OptionParam* param, std::string value)
{
    if (!param->IsSpecified())
    {
        return true;
    }
    else
    {
        std::string paramValue = param->Value();
        return paramValue == value;
    }
}

bool Program::MatchWhereParams(Spc::File& file)
{
    Spc::Header header = file.Header();
    Spc::Id666::Tag tag = file.Tag();

    if (!whereOption->IsSpecified())
    {
        return true;
    }
    else
    {
        bool matches = true;
        matches &= MatchWhereParam(idWhereParam.get(), header.id.ToString());
        matches &= MatchWhereParam(hasTagWhereParam.get(), 
                                   header.ContainsTag() ? "true" : "false");

        switch (tag.DetermineType())
        {
            case Spc::Id666::TagType::Text:
                matches &= MatchWhereParam(tagTypeWhereParam.get(), "text");
                break;
            case Spc::Id666::TagType::Binary:
                matches &= MatchWhereParam(tagTypeWhereParam.get(), "binary");
                break;
            case Spc::Id666::TagType::TextMixed:
                matches &= MatchWhereParam(tagTypeWhereParam.get(), 
                                           "textmixed");
                break;
        }

        matches &= MatchWhereParam(hasExtendedWhereParam.get(), 
                                   tag.HasExtendedData() ? "true" : "false");
        matches &= MatchWhereParam(songWhereParam.get(), 
                                   tag.SongTitle().ToString());
        matches &= MatchWhereParam(gameWhereParam.get(), 
                                   tag.GameTitle().ToString());
        matches &= MatchWhereParam(dumperWhereParam.get(), 
                                   tag.DumperName().ToString());
        matches &= MatchWhereParam(commentsWhereParam.get(), 
                                   tag.Comments().ToString());
        matches &= MatchWhereParam(dateWhereParam.get(), 
                                   tag.DateDumped().ToString());
        matches &= MatchWhereParam(songLengthWhereParam.get(), 
                                   tag.SongLength().ToString());
        matches &= MatchWhereParam(fadeLengthWhereParam.get(), 
                                   tag.FadeLength().ToString());
        matches &= MatchWhereParam(artistWhereParam.get(), 
                                   tag.SongArtist().ToString());
        matches &= MatchWhereParam(channelWhereParam.get(), 
                                   tag.DefaultDisabledChannels().ToString());
        matches &= MatchWhereParam(emulatorWhereParam.get(), 
                                   tag.EmulatorUsed().ToString());
        matches &= MatchWhereParam(titleWhereParam.get(), 
                                   tag.OstTitle().ToString());
        matches &= MatchWhereParam(discWhereParam.get(), 
                                   tag.OstDisc().ToString());
        matches &= MatchWhereParam(trackWhereParam.get(), 
                                   tag.OstTrack().ToString());
        matches &= MatchWhereParam(publisherWhereParam.get(), 
                                   tag.PublisherName().ToString());
        matches &= MatchWhereParam(copyrightWhereParam.get(), 
                                   tag.CopyrightYear().ToString());
        matches &= MatchWhereParam(introLengthWhereParam.get(), 
                                   tag.IntroLength().ToString());
        matches &= MatchWhereParam(loopLengthWhereParam.get(), 
                                   tag.LoopLength().ToString());
        matches &= MatchWhereParam(endLengthWhereParam.get(), 
                                   tag.EndLength().ToString());
        matches &= MatchWhereParam(mutedWhereParam.get(), 
                                   tag.MutedVoices().ToString());
        matches &= MatchWhereParam(loopTimesWhereParam.get(), 
                                   tag.LoopTimes().ToString());
        matches &= MatchWhereParam(preampWhereParam.get(), 
                                   tag.PreampLevel().ToString());

        return matches;
    }
}

int Program::ProcessSpcFile(const std::string& path)
{
    int result = 0;
    Spc::File file{ path };

    try
    {
        file.Load();
    }
    catch (const std::exception& e)
    {
        std::cerr << "ERROR: unable to open file: " << e.what() << std::endl;
        return 2;
    }

    if (!MatchWhereParams(file))
    {
        return 0;
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
        {
            result = PrintSpcFileDetailed(file);
        }
        else
        {
            result = PrintSpcFile(file);
        }
    }

    std::cout << std::endl;

    return result;
}

void Program::PrintLine(int length)
{
    for (int i = 0; i < length; ++i)
    {
        std::cout << '-';
    }

    std::cout << std::endl;
}

void Program::PrintHeading(std::string title)
{
    PrintLine(79);
    std::cout << title << std::endl;
    PrintLine(79);
}

void Program::PrintSubHeading(std::string title)
{
    std::cout << title << std::endl;
    PrintLine(79);
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
    PrintHeading(file.Path());
    std::cout << std::endl;
    PrintTag(file);
    return 0;
}

int Program::PrintSpcFileDetailed(Spc::File& file)
{
    Spc::Header header = file.Header();
    PrintHeading(file.Path());
    std::cout << std::endl;
    PrintFileHeader(header);
    std::cout << std::endl;
    PrintTag(file);
    return 0;
}

void Program::PrintFileHeader(Spc::Header& header)
{
    PrintSubHeading("SPC File Header");
    std::cout << header.ToString();
}

void Program::PrintTag(Spc::File& file)
{
    PrintSubHeading("ID666 Tag");
    Spc::Header header = file.Header();
    Spc::Id666::Tag tag = file.Tag();

    PrintHasTag(header);

    if (header.ContainsTag())
    {
        PrintTagType(tag);
        PrintHasExtended(tag);
        PrintField(tag.SongTitle());
        PrintField(tag.GameTitle());
        PrintField(tag.DumperName());
        PrintField(tag.Comments());
        PrintField(tag.DateDumped());
        PrintField(tag.SongLength());
        PrintField(tag.FadeLength());
        PrintField(tag.SongArtist());
        PrintField(tag.DefaultDisabledChannels());
        PrintField(tag.EmulatorUsed());
        PrintField(tag.OstTitle());
        PrintField(tag.OstDisc());
        PrintField(tag.OstTrack());
        PrintField(tag.PublisherName());
        PrintField(tag.CopyrightYear());
        PrintField(tag.IntroLength());
        PrintField(tag.LoopLength());
        PrintField(tag.EndLength());
        PrintField(tag.MutedVoices());
        PrintField(tag.LoopTimes());
        PrintField(tag.PreampLevel());
    }
}

void Program::PrintHasTag(Spc::Header& header)
{
    if (header.ContainsTag())
    {
        std::cout << Spc::FormatValue("Has ID666 Tag", "True") 
                  << std::endl;
    }
    else
    {
        std::cout << Spc::FormatValue("Has ID666 Tag", "False") 
                  << std::endl;
    }
}

void Program::PrintTagType(Spc::Id666::Tag& tag)
{
    switch (tag.DetermineType())
    {
        case Spc::Id666::TagType::Text:
            std::cout << Spc::FormatValue("Tag Type", "Text") << std::endl;
            break;
        case Spc::Id666::TagType::Binary:
            std::cout << Spc::FormatValue("Tag Type", "Binary") 
                      << std::endl;
            break;
        case Spc::Id666::TagType::TextMixed:
            std::cout << Spc::FormatValue("Tag Type", "Text (Mixed)") 
                      << std::endl;
            break;
        default:
            std::cout << Spc::FormatValue("Tag Type", "Unknown") 
                      << std::endl;
    }
}

void Program::PrintHasExtended(Spc::Id666::Tag& tag)
{
    if (tag.ExtendedData() != nullptr)
    {
            if (tag.HasExtendedData())
            {
                std::cout << Spc::FormatValue("Has Extended Tag Data", "True")
                          << std::endl;
            }
            else
            {
                std::cout << Spc::FormatValue("Has Extended Tag Data", "False")
                          << std::endl;
            }
    }
    else
    {
        std::cout << Spc::FormatValue("Has Extended Tag Data", "False")
                  << std::endl;
    }
}

int Program::PrintSpecifiedItems(Spc::File& file)
{
    Spc::Header header = file.Header();
    Spc::Id666::Tag tag = file.Tag();

    PrintHeading(file.Path());
    std::cout << std::endl;

    if (headerPrintParam->IsSpecified())
        PrintFileHeader(header);

    if (idPrintParam->IsSpecified())
        PrintField(header.id);

    if (hasTagPrintParam->IsSpecified())
        PrintHasTag(header);

    if (tagPrintParam->IsSpecified())
        PrintTag(file);

    if (tagTypePrintParam->IsSpecified())
        PrintTagType(tag);

    if (hasExtendedPrintParam->IsSpecified())
        PrintHasExtended(tag);

    if (songPrintParam->IsSpecified())
        PrintField(tag.SongTitle());

    if (gamePrintParam->IsSpecified())
        PrintField(tag.GameTitle());

    if (dumperPrintParam->IsSpecified())
        PrintField(tag.DumperName());

    if (commentsPrintParam->IsSpecified())
        PrintField(tag.Comments());
    
    if (datePrintParam->IsSpecified())
        PrintField(tag.DateDumped());

    if (songLengthPrintParam->IsSpecified())
        PrintField(tag.SongLength());

    if (fadeLengthPrintParam->IsSpecified())
        PrintField(tag.FadeLength());

    if (artistPrintParam->IsSpecified())
        PrintField(tag.SongArtist());

    if (channelPrintParam->IsSpecified())
        PrintField(tag.DefaultDisabledChannels());

    if (emulatorPrintParam->IsSpecified())
        PrintField(tag.EmulatorUsed());

    if (titlePrintParam->IsSpecified())
        PrintField(tag.OstTitle());

    if (discPrintParam->IsSpecified())
        PrintField(tag.OstDisc());

    if (trackPrintParam->IsSpecified())
        PrintField(tag.OstTrack());

    if (publisherPrintParam->IsSpecified())
        PrintField(tag.PublisherName());

    if (copyrightPrintParam->IsSpecified())
        PrintField(tag.CopyrightYear());

    if (introLengthPrintParam->IsSpecified())
        PrintField(tag.IntroLength());

    if (loopLengthPrintParam->IsSpecified())
        PrintField(tag.LoopLength());

    if (endLengthPrintParam->IsSpecified())
        PrintField(tag.EndLength());

    if (mutedPrintParam->IsSpecified())
        PrintField(tag.MutedVoices());

    if (loopTimesPrintParam->IsSpecified())
        PrintField(tag.LoopTimes());

    if (preampPrintParam->IsSpecified())
        PrintField(tag.PreampLevel());

    //std::cout << std::endl;

    return 0;
}

int Program::EditSpecifiedItems(Spc::File& file)
{
    PrintHeading(file.Path());
    std::cout << std::endl;

    Spc::Id666::Tag tag = file.Tag();

    if (songEditParam->IsSpecified())
    {
        tag.SetSongTitle(songEditParam->Value());
        PrintField(tag.SongTitle());
    }

    if (gameEditParam->IsSpecified())
    {
        tag.SetGameTitle(gameEditParam->Value());
        PrintField(tag.GameTitle());
    }

    if (dumperEditParam->IsSpecified())
    {
        tag.SetDumperName(dumperEditParam->Value());
        PrintField(tag.DumperName());
    }

    if (commentsEditParam->IsSpecified())
    {
        tag.SetComments(commentsEditParam->Value());
        PrintField(tag.Comments());
    }

    if (dateEditParam->IsSpecified())
    {
        tag.SetDateDumped(dateEditParam->Value());
        PrintField(tag.DateDumped());
    }

    if (songLengthEditParam->IsSpecified())
    {
        tag.SetSongLength(songLengthEditParam->Value());
        PrintField(tag.SongLength());
    }

    if (fadeLengthEditParam->IsSpecified())
    {
        tag.SetFadeLength(fadeLengthEditParam->Value());
        PrintField(tag.FadeLength());
    }

    if (artistEditParam->IsSpecified())
    {
        tag.SetSongArtist(artistEditParam->Value());
        PrintField(tag.SongArtist());
    }

    if (channelEditParam->IsSpecified())
    {
        tag.SetDefaultDisabledChannels(channelEditParam->Value());
        PrintField(tag.DefaultDisabledChannels());
    }

    if (emulatorEditParam->IsSpecified())
    {
        tag.SetEmulatorUsed(emulatorEditParam->Value());
        PrintField(tag.EmulatorUsed());
    }

    if (titleEditParam->IsSpecified())
    {
        tag.SetOstTitle(titleEditParam->Value());
        PrintField(tag.OstTitle());
    }

    if (discEditParam->IsSpecified())
    {
        tag.SetOstDisc(discEditParam->Value());
        PrintField(tag.OstDisc());
    }

    if (trackEditParam->IsSpecified())
    {
        tag.SetOstTrack(trackEditParam->Value());
        PrintField(tag.OstTrack());
    }

    if (publisherEditParam->IsSpecified())
    {
        tag.SetPublisherName(publisherEditParam->Value());
        PrintField(tag.PublisherName());
    }

    if (copyrightEditParam->IsSpecified())
    {
        tag.SetCopyrightYear(copyrightEditParam->Value());
        PrintField(tag.CopyrightYear());
    }

    if (introLengthEditParam->IsSpecified())
    {
        tag.SetIntroLength(introLengthEditParam->Value());
        PrintField(tag.IntroLength());
    }

    if (loopLengthEditParam->IsSpecified())
    {
        tag.SetLoopLength(loopLengthEditParam->Value());
        PrintField(tag.LoopLength());
    }

    if (endLengthEditParam->IsSpecified())
    {
        tag.SetEndLength(endLengthEditParam->Value());
        PrintField(tag.EndLength());
    }

    if (mutedEditParam->IsSpecified())
    {
        tag.SetMutedVoices(mutedEditParam->Value());
        PrintField(tag.MutedVoices());
    }

    if (loopTimesEditParam->IsSpecified())
    {
        tag.SetLoopTimes(loopTimesEditParam->Value());
        PrintField(tag.LoopTimes());
    }

    if (preampEditParam->IsSpecified())
    {
        tag.SetPreampLevel(preampEditParam->Value());
        PrintField(tag.PreampLevel());
    }

    file.SetTag(tag);
        
    file.Save();

    //std::cout << std::endl;
        
    return 0;
}

int Program::IncrementTrack(Spc::File& file)
{
    Spc::Id666::Tag tag = file.Tag();
    uint8_t track = tag.OstTrack().ToUInt32();
    int incrementAmount = std::stoi(incrementOption->Values()[0]);
    track += incrementAmount;
    tag.SetOstTrack(std::to_string(track));
    file.SetTag(tag);
    file.Save();
    return 0;
}

int Program::Run(std::vector<std::string> arguments)
{
    DefineParams();
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