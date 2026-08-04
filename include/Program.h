// Program.h - Declares the Program class.
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

#ifndef PROGRAM_H
#define PROGRAM_H

#include <memory>
#include <vector>
#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
#include <LibCppCmdLine.h>
#include <LibCppSpc.h>

/// @brief Indicates the program exited successfully.
inline constexpr int exitStatusSuccess{ 0 };

/// @brief Indicates the program exited with a failure.
inline constexpr int exitStatusFailure{ 1 };

/// @brief Provides the main program logic for the command line version.
class Program
{
public:
    /// @brief Runs the main program.
    /// @param arguments The command line arguments passed into the program.
    /// @return Returns a status code for the main method to use.
    int Run(const std::vector<std::string>& arguments);
private:
    std::unique_ptr<CmdLine::ProgParam> progParam;
    std::unique_ptr<CmdLine::MultiPosParam> spcFileParam;
    std::unique_ptr<CmdLine::ValueOption> printOption;
    std::unique_ptr<CmdLine::ValueOption> editOption;
    std::unique_ptr<CmdLine::ValueOption> whereOption;
    std::unique_ptr<CmdLine::ValueOption> fileNameToTagOption;
    std::unique_ptr<CmdLine::ValueOption> tagToFileNameOption;
    std::unique_ptr<CmdLine::ValueOption> incrementOption;
    std::unique_ptr<CmdLine::Option> detailedOption;
    std::unique_ptr<CmdLine::Option> versionOption;
    std::unique_ptr<CmdLine::OptionParam> idPrintParam;
    std::unique_ptr<CmdLine::OptionParam> hasTagPrintParam;
    std::unique_ptr<CmdLine::OptionParam> tagPrintParam;
    std::unique_ptr<CmdLine::OptionParam> headerPrintParam;
    std::unique_ptr<CmdLine::OptionParam> tagTypePrintParam;
    std::unique_ptr<CmdLine::OptionParam> hasExtendedPrintParam;
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
    std::unique_ptr<CmdLine::OptionParam> fadeLengthExtPrintParam;
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
    std::unique_ptr<CmdLine::OptionParam> fadeLengthExtEditParam;
    std::unique_ptr<CmdLine::OptionParam> mutedEditParam;
    std::unique_ptr<CmdLine::OptionParam> loopTimesEditParam;
    std::unique_ptr<CmdLine::OptionParam> preampEditParam;
    std::unique_ptr<CmdLine::OptionParam> idWhereParam;
    std::unique_ptr<CmdLine::OptionParam> hasTagWhereParam;
    std::unique_ptr<CmdLine::OptionParam> tagWhereParam;
    std::unique_ptr<CmdLine::OptionParam> headerWhereParam;
    std::unique_ptr<CmdLine::OptionParam> tagTypeWhereParam;
    std::unique_ptr<CmdLine::OptionParam> hasExtendedWhereParam;
    std::unique_ptr<CmdLine::OptionParam> songWhereParam;
    std::unique_ptr<CmdLine::OptionParam> gameWhereParam;
    std::unique_ptr<CmdLine::OptionParam> dumperWhereParam;
    std::unique_ptr<CmdLine::OptionParam> commentsWhereParam;
    std::unique_ptr<CmdLine::OptionParam> dateWhereParam;
    std::unique_ptr<CmdLine::OptionParam> songLengthWhereParam;
    std::unique_ptr<CmdLine::OptionParam> fadeLengthWhereParam;
    std::unique_ptr<CmdLine::OptionParam> artistWhereParam;
    std::unique_ptr<CmdLine::OptionParam> channelWhereParam;
    std::unique_ptr<CmdLine::OptionParam> emulatorWhereParam;
    std::unique_ptr<CmdLine::OptionParam> titleWhereParam;
    std::unique_ptr<CmdLine::OptionParam> discWhereParam;
    std::unique_ptr<CmdLine::OptionParam> trackWhereParam;
    std::unique_ptr<CmdLine::OptionParam> publisherWhereParam;
    std::unique_ptr<CmdLine::OptionParam> copyrightWhereParam;
    std::unique_ptr<CmdLine::OptionParam> introLengthWhereParam;
    std::unique_ptr<CmdLine::OptionParam> loopLengthWhereParam;
    std::unique_ptr<CmdLine::OptionParam> endLengthWhereParam;
    std::unique_ptr<CmdLine::OptionParam> fadeLengthExtWhereParam;
    std::unique_ptr<CmdLine::OptionParam> mutedWhereParam;
    std::unique_ptr<CmdLine::OptionParam> loopTimesWhereParam;
    std::unique_ptr<CmdLine::OptionParam> preampWhereParam;
    std::unique_ptr<CmdLine::Parser> parser;

    /// @brief Prints information about the program to the screen.
    void PrintVersion();

    /// @brief Defines the positional parameters for command line arguments.
    void DefinePosParams();

    /// @brief Defines the options for command line arguments.
    void DefineOptions();

    /// @brief Defines the option parameters for command line arguments.
    void DefineOptionParams();

    /// @brief Defines the command line parameters the program supports.
    ///
    /// Builds the CmdLine::Param objects that define the parameters that
    /// interpret the command line arguments passed to the program. Once
    /// defined, the program can use the CmdLine::Parser to parse the arguments
    /// and automatically generate usage information for the program.
    void DefineParams();

    /// @brief Initializes the CmdLine::Parser.
    /// @param arguments The command line arguments to load into the parser.
    void InitializeParser(const std::vector<std::string>& arguments);

    /// @brief Selects the program's mode of operation based on the arguments.
    /// @return The status code returned by the selected mode upon completion.
    int SelectMode();

    /// @brief Checks if a specific where parameter matches the given value.
    /// @param param The where parameter to check.
    /// @param value The value to match against.
    /// @return True if the parameter matches the value, false otherwise.
    bool MatchWhereParam(const CmdLine::OptionParam* param, 
                         const std::string& value);

    /// @brief Matches the .spc file against the specified where parameters.
    ///
    /// The -w, --where option allows the user to specify sets of field-value
    /// pairs in the .spc file that must match specific values. This allows the
    /// user to filter out any files that do not have the matching attribute
    /// values.
    ///
    /// @param file The SPC file to match.
    /// @return True if the file matches the where parameters, false otherwise.
    bool MatchWhereParams(const Spc::File& file);

    /// @brief Processes one SPC file using the mode selected by args.
    /// @param path The path to the SPC file to process.
    /// @return The status code returned by the selected operation.
    int ProcessSpcFile(const std::string& path);

    /// @brief Prints a line of the specified length to the console.
    /// @param length The number of characters to print in the line.
    void PrintLine(int length);

    /// @brief Prints a heading to the console.
    /// @param title The title of the heading.
    void PrintHeading(const std::string& title);

    /// @brief Prints a sub-heading to the console.
    /// @param title The title of the sub-heading.
    void PrintSubHeading(const std::string& title);

    /// @brief Prints the specified SPC field to the console.
    /// @param field The field to print.
    void PrintField(const Spc::Field& field);

    /// @brief Prints tag information from the SPC file to the console.
    /// @param file The SPC file to print.
    /// @return The status code returned by the operation.
    int PrintSpcFile(const Spc::File& file);

    /// @brief Prints the entire SPC file's metadata including tags & headers.
    /// @return The status code returned by the operation.
    int PrintSpcFileDetailed(const Spc::File& file);

    /// @brief Prints the SPC file header.
    /// @param header The header to print.
    void PrintFileHeader(const Spc::Header& header);

    /// @brief Prints all tag information, including the extended tag info.
    /// @param stream The file stream to print the tag from.
    void PrintTag(const Spc::File& file);

    /// @brief Prints whether the SPC file header indicates a tag is present.
    /// @param header The header to check.
    void PrintHasTag(const Spc::Header& header);

    /// @brief Prints the type of the ID666 tag (text, binary, or mixed).
    /// @param tag The tag to check.
    void PrintTagType(const Spc::Id666::Tag& tag);

    /// @brief Prints whether the ID666 tag has extended information.
    /// @param tag The tag to check.
    void PrintHasExtended(const Spc::Id666::Tag& tag);

    /// @brief Prints the text formattted ID666 tag.
    /// @param file The file stream to use for printing.
    void PrintTextTag(const Spc::File& file);

    /// @brief Prints the binary formatted ID666 tag.
    /// @param file The file stream to use for printing.
    void PrintBinaryTag(const Spc::File& file);

    /// @brief Prints the extended ID666 tag.
    /// @param file The file to use for printing. 
    void PrintExtendedTag(const Spc::File& file);

    /// @brief Prints the items in the .spc file that were specified via args.
    int PrintSpecifiedItems(const Spc::File& file);

    /// @brief Edits the items in the .spc file that were specified via args.
    /// @param file The file to edit.
    /// @return The status code.
    int EditSpecifiedItems(Spc::File& file);

    /// @brief Increments the track number by amount specified in cmdline args.
    /// @param file The file to edit.
    /// @return The status code.
    int IncrementTrack(Spc::File& file);
};

#endif