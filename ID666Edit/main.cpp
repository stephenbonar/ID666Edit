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
#include "DataField.h"
#include "RawFileStream.h"
#include "SpcHeader.h"

void PrintField(std::string label, Binary::DataField* field)
{
    std::cout << std::setw(20) << std::left << label << ": "
              << field->ToString() << std::endl;
}

void PrintHeader(SpcHeader& header)
{
    PrintField("SPC Header ID", &header.ID);
    PrintField("Separator", &header.separator);
    PrintField("Contains Tag", &header.containsTag);
    PrintField("Version Minor", &header.versionMinor);
    
    std::cout << std::endl;

    PrintField("PC Register", &header.pcRegister);
    PrintField("A Register", &header.aRegister);
    PrintField("X Register", &header.xRegister);
    PrintField("Y Register", &header.yRegister);
    PrintField("PSW Register", &header.pswRegister);
    PrintField("SP (lower byte)", &header.spRegister);
    PrintField("Reserved", &header.reserved);
}

int main(int, char**)
{
    std::cout << "ID666Edit v0.1" << std::endl;
    std::cout << "Copyright (C) 2025 Stephen Bonar" << std::endl << std::endl;

    Binary::RawFileStream fileStream{ "test.spc" };
    fileStream.Open(Binary::FileMode::Read);

    if (fileStream.IsOpen())
    {
        std::cout << "File opened successfully." << std::endl << std::endl;

        SpcHeader header;
        fileStream.Read(&header);
        fileStream.Close();
        PrintHeader(header);
    }
    else
    {
        std::cerr << "Unable to open file " << fileStream.FileName()
                  << std::endl << std::endl;
    }
    
    return 0;
}
