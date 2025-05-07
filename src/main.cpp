// main.cpp - Defines the ID666Edit main program entrypoint.
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

#include <iostream>
#include <iomanip>
#include <vector>
#include "CmdLine.h"
#include "DataField.h"
#include "RawFileStream.h"
#include "SpcHeader.h"
#include "SpcFile.h"

void PrintField(std::string label, std::string value)
{
    std::cout << std::setw(25) << std::left << label << ": "
              << value << std::endl;
}

void PrintHeader(SpcHeader& header)
{
    PrintField("SPC Header ID", header.ID.ToString());
    PrintField("Separator", header.separator.ToString());
    PrintField("Contains Tag", header.containsTag.ToString());
    PrintField("Version Minor", header.versionMinor.ToString());
    
    std::cout << std::endl;

    PrintField("PC Register", header.pcRegister.ToString());
    PrintField("A Register", header.aRegister.ToString());
    PrintField("X Register", header.xRegister.ToString());
    PrintField("Y Register", header.yRegister.ToString());
    PrintField("PSW Register", header.pswRegister.ToString());
    PrintField("SP (lower byte)", header.spRegister.ToString());
    PrintField("Reserved", header.reserved.ToString());
}

void PrintTextTag(ID666TextTag& tag)
{
    PrintField("Song Title", tag.songTitle.ToString());
    PrintField("Game Title", tag.gameTitle.ToString());
    PrintField("Dumper", tag.dumperName.ToString());
    PrintField("Comments", tag.comments.ToString());
    PrintField("Date Dumped", tag.dateDumped.ToString());
    PrintField("Song Length (sec)", tag.songLength.ToString());
    PrintField("Fade Length (ms)", tag.fadeLength.ToString());
    PrintField("Artist", tag.songArtist.ToString());
    PrintField("Default Channel Disables", tag.defaultChannelDisables.ToString());
    PrintField("Emulator Used", tag.emulatorUsed.ToString());
    PrintField("Reserved", tag.reserved.ToString());
}

int main(int argc, char** argv)
{
    std::vector<std::string> arguments;

    std::cout << "ID666Edit v0.1" << std::endl;
    std::cout << "Copyright (C) 2025 Stephen Bonar" << std::endl << std::endl;

    for (int i = 0; i < argc; i++)
        arguments.push_back(argv[i]);

    CmdLine::ProgParam::Definition progParamDef;
    progParamDef.name = "ID666Edit";
    progParamDef.description = "An ID666 metadata tag editor for .SPC files.";
    CmdLine::ProgParam progParam{ progParamDef };

    CmdLine::PosParam::Definition spcFileParamDef;
    spcFileParamDef.name = "spc_file";
    spcFileParamDef.description = "The SPC file to open.";
    spcFileParamDef.isMandatory = true;
    CmdLine::PosParam spcFileParam{ spcFileParamDef };
    
    CmdLine::Parser parser{ &progParam, arguments };
    parser.Add(&spcFileParam);
    CmdLine::Parser::Status status = parser.Parse();

    if (status == CmdLine::Parser::Status::Success && 
        spcFileParam.IsSpecified())
    {
        SpcFile file{ spcFileParam.Value() };
        SpcHeader header;
        file.Open();
        file.Read(&header);
        PrintHeader(header);
        std::cout << std::endl;

        if (file.HeaderContainsTag())
        {
            PrintField("Header Contains Tag", "True");

            if (file.HasBinaryTag())
            {
                PrintField("Tag Type", "Binary");
            }
            else
            {
                PrintField("Tag Type", "Text");
                std::cout << std::endl;

                ID666TextTag tag;
                file.Read(&tag);
                PrintTextTag(tag);
            }
        }
        else
        {
            PrintField("Header Contains Tag", "False");
        }

        return 0;
    }
    else
    {
        std::cerr << parser.GenerateUsage();
        return 1;
    }
}
