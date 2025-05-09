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

#include <vector>
#include "Program.h"

int main(int argc, char** argv)
{
    std::vector<std::string> arguments;

    for (int i = 0; i < argc; i++)
        arguments.push_back(argv[i]);

    Program program;
    return program.Run(arguments);

    /*
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
        std::cout << header.ToString();

        //PrintHeader(header);
        std::cout << std::endl;

        if (file.HeaderContainsTag())
        {
            std::cout << FormatValue("Header Contains Tag", "True");

            if (file.HasBinaryTag())
            {
                std::cout << FormatValue("Tag Type", "Binary");
            }
            else
            {
                std::cout << FormatValue("Tag Type", "Text");
                std::cout << std::endl;

                ID666TextTag tag;
                file.Read(&tag);
                std::cout << tag.ToString();

                if (file.HasExtendedTag())
                {
                    std::cout << "Has extended tag!" << std::endl;
                    file.SeekExtendedTag();

                    Binary::ChunkHeader tagHeader;
                    file.Read(&tagHeader);
                    std::cout << FormatValue("Extended Tag ID", tagHeader.id.Value());
                    std::cout << FormatValue("Extended Tag Size", tagHeader.dataSize.ToString());
                }
            }
        }
        else
        {
            std::cout << FormatValue("Header Contains Tag", "False");
        }

        return 0;
    }
    else
    {
        std::cerr << parser.GenerateUsage();
        return 1;
    }
    */
}
