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
#include "LibCppCmdLine.h"
#include "SpcHeader.h"
#include "SpcFile.h"
#include "SpcFormat.h"
#include "ID666ExtendedItem.h"

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
    std::unique_ptr<CmdLine::MultiPosParam> spcFileParam;
    std::unique_ptr<CmdLine::ValueOption> printOption;
    std::unique_ptr<CmdLine::ValueOption> editOption;
    std::unique_ptr<CmdLine::ValueOption> fileNameToTagOption;
    std::unique_ptr<CmdLine::ValueOption> tagToFileNameOption;
    std::unique_ptr<CmdLine::Option> detailedOption;
    std::unique_ptr<CmdLine::Option> versionOption;
    std::unique_ptr<CmdLine::OptionParam> tagPrintParam;
    std::unique_ptr<CmdLine::OptionParam> headerPrintParam;
    std::unique_ptr<CmdLine::OptionParam> songPrintParam;
    std::unique_ptr<CmdLine::OptionParam> gamePrintParam;
    std::unique_ptr<CmdLine::OptionParam> dumperPrintParam;
    std::unique_ptr<CmdLine::OptionParam> commentsPrintParam;
    std::unique_ptr<CmdLine::OptionParam> datePrintParam;
    std::unique_ptr<CmdLine::OptionParam> songLengthPrintParam;
    std::unique_ptr<CmdLine::OptionParam> fadeLengthPrintParam;
    std::unique_ptr<CmdLine::OptionParam> artistPrintParam;
    std::unique_ptr<CmdLine::OptionParam> channelPrintParam;
    std::unique_ptr<CmdLine::OptionParam> emulatorPrintParam;
    std::unique_ptr<CmdLine::OptionParam> titlePrintParam;
    std::unique_ptr<CmdLine::OptionParam> discPrintParam;
    std::unique_ptr<CmdLine::OptionParam> trackPrintParam;
    std::unique_ptr<CmdLine::OptionParam> publisherPrintParam;
    std::unique_ptr<CmdLine::OptionParam> copyrightPrintParam;
    std::unique_ptr<CmdLine::OptionParam> introLengthPrintParam;
    std::unique_ptr<CmdLine::OptionParam> loopLengthPrintParam;
    std::unique_ptr<CmdLine::OptionParam> endLengthPrintParam;
    std::unique_ptr<CmdLine::OptionParam> mutedPrintParam;
    std::unique_ptr<CmdLine::OptionParam> loopTimesPrintParam;
    std::unique_ptr<CmdLine::OptionParam> preampPrintParam;
    std::unique_ptr<CmdLine::OptionParam> songEditParam;
    std::unique_ptr<CmdLine::OptionParam> gameEditParam;
    std::unique_ptr<CmdLine::OptionParam> dumperEditParam;
    std::unique_ptr<CmdLine::OptionParam> commentsEditParam;
    std::unique_ptr<CmdLine::OptionParam> dateEditParam;
    std::unique_ptr<CmdLine::OptionParam> songLengthEditParam;
    std::unique_ptr<CmdLine::OptionParam> fadeLengthEditParam;
    std::unique_ptr<CmdLine::OptionParam> artistEditParam;
    std::unique_ptr<CmdLine::OptionParam> channelEditParam;
    std::unique_ptr<CmdLine::OptionParam> emulatorEditParam;
    std::unique_ptr<CmdLine::OptionParam> titleEditParam;
    std::unique_ptr<CmdLine::OptionParam> discEditParam;
    std::unique_ptr<CmdLine::OptionParam> trackEditParam;
    std::unique_ptr<CmdLine::OptionParam> publisherEditParam;
    std::unique_ptr<CmdLine::OptionParam> copyrightEditParam;
    std::unique_ptr<CmdLine::OptionParam> introLengthEditParam;
    std::unique_ptr<CmdLine::OptionParam> loopLengthEditParam;
    std::unique_ptr<CmdLine::OptionParam> endLengthEditParam;
    std::unique_ptr<CmdLine::OptionParam> mutedEditParam;
    std::unique_ptr<CmdLine::OptionParam> loopTimesEditParam;
    std::unique_ptr<CmdLine::OptionParam> preampEditParam;
    std::unique_ptr<CmdLine::Parser> parser;

    /// @brief Prints information about the program to the screen.
    void PrintVersion();

    /// @brief Defines the command line parameters the program supports.
    ///
    /// Builds the CmdLine::Param objects that define the parameters that
    /// interpret the command line arguments passed to the program. Once
    /// defined, the program can use the CmdLine::Parser to parse the arguments
    /// and automatically generate usage information for the program.
    void DefineParameters();

    /// @brief Initializes the CmdLine::Parser.
    /// @param arguments The command line arguments to load into the parser.
    void InitializeParser(std::vector<std::string> arguments);

    /// @brief Selects the program's mode of operation based on the arguments.
    /// @return The status code returned by the selected mode upon completion.
    int SelectMode();

    void PrintSectionHeader(std::string title);

    void PrintSectionHeader(std::string title, int length);

    void PrintField(SpcField* field);

    void PrintField(SpcTextField field);

    void PrintField(SpcDateField field);

    void PrintField(SpcNumericField field);

    void PrintField(SpcTrackField field);

    void PrintField(SpcEmulatorField field);

    void PrintField(SpcBinaryField field);

    int PrintSpcFile(SpcFile& file);

    /// @brief Prints the entire SPC file's metadata including tags & headers.
    /// @return The status code returned by the operation.
    int PrintSpcFileDetailed(SpcFile& file);

    /// @brief Prints the SPC file header.
    /// @param file The file stream to print the header from.
    void PrintHeader(SpcFile& file);

    /// @brief Prints all tag information, including the extended tag info.
    /// @param stream The file stream to print the tag from.
    void PrintTag(SpcFile& file);

    /// @brief Prints the text formattted ID666 tag.
    /// @param file The file stream to use for printing.
    void PrintTextTag(SpcFile& file);

    /// @brief Prints the binary formatted ID666 tag.
    /// @param file The file stream to use for printing.
    void PrintBinaryTag(SpcFile& file);

    /// @brief Prints the extended ID666 tag.
    /// @param file The file to use for printing. 
    void PrintExtendedTag(SpcFile& file);

    /// @brief Prints the items in the .spc file that were specified via args.
    int PrintSpecifiedItems(SpcFile& file);

    /// @brief Edits the items in the .spc file that were specified via args.
    /// @param file The file to edit.
    /// @return The status code.
    int EditSpecifiedItems(SpcFile& file);
};

#endif