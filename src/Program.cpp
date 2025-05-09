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
    SpcFile file{ spcFileParam->Value() };
    SpcHeader header;
    file.Open();

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
        {
            std::cout << FormatValue("Tag Type", "Binary") << std::endl;
        }
        else
        {
            PrintTextTag(file);
        }
    }
    else
    {
        std::cout << FormatValue("Header Contains Tag", "False");
    }

    if (file.HasExtendedTag())
    {
        PrintExtendedTag(file);
    }
    else
    {
        std::cout << FormatValue("Has Extended Tag", "False") << std::endl;
    }

    return 0;
}

void Program::PrintTextTag(SpcFile& file)
{
    std::cout << FormatValue("Tag Type", "Text") << std::endl;
    std::cout << std::endl;

    ID666TextTag tag;
    file.Read(&tag);
    std::cout << tag.ToString() << std::endl;
}

void Program::PrintExtendedTag(SpcFile& file)
{
    std::cout << FormatValue("Has Extended Tag", "True") << std::endl;
    file.SeekExtendedTag();

    Binary::ChunkHeader tagHeader;
    file.Read(&tagHeader);
    std::string id = tagHeader.id.Value();
    std::string size = tagHeader.dataSize.ToString();
    std::cout << FormatValue("Extended Tag ID", id) << std::endl;
    std::cout << FormatValue("Extended Tag Size", size) << std::endl;
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