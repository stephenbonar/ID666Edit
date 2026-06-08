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
        const std::vector<std::string> spcFiles = spcFileParam->Values();

        for (const std::string& value : spcFiles)
        {
            int result = ProcessSpcFile(value);

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

    return result;
}

void Program::PrintSectionHeader(std::string title)
{
    PrintSectionHeader(title, title.length());
}

void Program::PrintSectionHeader(std::string title, int length)
{
    std::cout << title << std::endl;

    for (int i = 0; i < length; ++i)
    {
        std::cout << '-';
    }

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
    PrintSectionHeader(file.Path(), 79);
    PrintTag(file);
    return 0;
}

int Program::PrintSpcFileDetailed(Spc::File& file)
{
    PrintSectionHeader(file.Path(), 79);
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
    Spc::Header header = file.Header();
    Spc::Id666::Tag tag = file.Tag();

    if (header.containsTag.ToUInt32() == Spc::headerContainsTag)
    {
        std::cout << Spc::FormatValue("Header Contains Tag", "True") 
                  << std::endl;
        
        if (tag.ExtendedData() != nullptr)
        {
            if (tag.ExtendedData()->SpcFields().size() > 0)
            {
                std::cout << Spc::FormatValue("Has Extended Tag", "True")
                          << std::endl;
            }
            else
            {
                std::cout << Spc::FormatValue("Has Extended Tag", "False")
                          << std::endl;
            }
        }
        else
        {
            std::cout << Spc::FormatValue("Has Extended Tag", "False")
                      << std::endl;
        }

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
    else
    {
        std::cout << Spc::FormatValue("Header Contains Tag", "False") 
                  << std::endl;
    }
}

int Program::PrintSpecifiedItems(Spc::File& file)
{
    PrintSectionHeader(file.Path(), 79);

    if (headerPrintParam->IsSpecified())
        PrintHeader(file);

    Spc::Id666::Tag tag = file.Tag();

    if (tagPrintParam->IsSpecified())
        PrintTag(file);

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

    std::cout << std::endl;

    return 0;
}

int Program::EditSpecifiedItems(Spc::File& file)
{
    PrintSectionHeader(file.Path(), 79);

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

    std::cout << std::endl;
        
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