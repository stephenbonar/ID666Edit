// Program.h - Declares the Program class.
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

#ifndef PROGRAM_H
#define PROGRAM_H

#include <memory>
#include <vector>
#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
#include "CmdLine.h"
#include "DataField.h"
#include "RawFileStream.h"
#include "SpcHeader.h"
#include "SpcFile.h"
#include "SpcFormat.h"
#include "ExtendedID666Item.h"

class Program
{
public:
    int Run(std::vector<std::string> arguments);
private:
    std::unique_ptr<CmdLine::ProgParam> progParam;
    std::unique_ptr<CmdLine::PosParam> spcFileParam;
    std::unique_ptr<CmdLine::Parser> parser;

    void PrintProgramInfo();
    void DefineCmdLineParameters();
    void InitializeCmdLineParser(std::vector<std::string> arguments);
    int SelectMode();
    int PrintSpcFile();
    void PrintTextTag(SpcFile& file);
    void PrintBinaryTag(SpcFile& file);
    void PrintExtendedTag(SpcFile& file);
    void PrintExtendedItem(ExtendedID666Item& item);
    void PrintExtendedItem(ExtendedID666Item& item, 
        Binary::StringField& field);
    void PrintExtendedItem(ExtendedID666Item& item, 
        Binary::UInt32Field& field);
};

#endif