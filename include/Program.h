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
#include "SpcFileStream.h"
#include "SpcFormat.h"
#include "ExtendedID666Item.h"

/// @brief Provides the main program logic.
class Program
{
public:
    /// @brief Runs the main program.
    /// @param arguments The command line arguments passed into the program.
    /// @return Returns a statust code for the main method to use.
    int Run(std::vector<std::string> arguments);
private:
    std::unique_ptr<CmdLine::ProgParam> progParam;
    std::unique_ptr<CmdLine::PosParam> spcFileParam;
    std::unique_ptr<CmdLine::Parser> parser;

    /// @brief Prints information about the program to the screen.
    void PrintProgramInfo();

    /// @brief Defines the command line parameters the program supports.
    ///
    /// Builds the CmdLine::Param objects that define the parameters that
    /// interpret the command line arguments passed to the program. Once
    /// defined, the program can use the CmdLine::Parser to parse the arguments
    /// and automatically generate usage information for the program.
    void DefineCmdLineParameters();

    /// @brief Initializes the CmdLine::Parser.
    /// @param arguments The command line arguments to load into the parser.
    void InitializeCmdLineParser(std::vector<std::string> arguments);

    /// @brief Selects the program's mode of operation based on the arguments.
    /// @return The status code returned by the selected mode upon completion.
    int SelectMode();

    /// @brief Prints the entire SPC file's metadata including tags & headers.
    /// @return The status code returned by the operation.
    int PrintSpcFile();

    /// @brief Prints the text formattted ID666 tag.
    /// @param file The file stream to use for printing.
    void PrintTextTag(SpcFileStream& file);

    /// @brief Prints the binary formatted ID666 tag.
    /// @param file The file stream to use for printing.
    void PrintBinaryTag(SpcFileStream& file);

    /// @brief Prints the extended ID666 tag.
    /// @param file The file stream to use for printing. 
    void PrintExtendedTag(SpcFileStream& file);

    /// @brief Prints the specified ID666 extended tag item.
    ///
    /// Use this method to print extended tag items where the value is stored
    /// directly in the item's header data field.
    ///
    /// @param item The item to print.
    void PrintExtendedItem(ExtendedID666Item& item);

    /// @brief Prints the specified ID666 extended tag item.
    /// @param item The item to print.
    /// @param field The associated string data field beyond the tag header.
    void PrintExtendedItem(ExtendedID666Item& item, 
        Binary::StringField& field);

    /// @brief Prints the specified ID666 extended tag item.
    /// @param item The item to print.
    /// @param field The associated int data field beyond the tag header.
    void PrintExtendedItem(ExtendedID666Item& item, 
        Binary::UInt32Field& field);
};

#endif