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
#include "StringField.h"
#include "RawField.h"
#include "IntField.h"
#include "RawFileStream.h"

void PrintField(std::string label, std::string value)
{
    std::cout << std::setw(20) << std::left << label << ": "
              << value << std::endl;
}

void PrintRawField(std::string label, Binary::DataField* field)
{
    PrintField(label, field->ToString(Binary::StringFormat::Hex));
}

int main(int, char**)
{
    std::cout << "ID666Edit v0.1" << std::endl;
    std::cout << "Copyright (C) 2025 Stephen Bonar" << std::endl << std::endl;

    Binary::StringField headerID{ 33 };
    Binary::RawField separator{ 2 };
    Binary::UInt8Field containsTag;
    Binary::UInt8Field versionMinor;

    Binary::RawField pcRegister{ 2 };
    Binary::RawField aRegister{ 1 };
    Binary::RawField xRegister{ 1 };
    Binary::RawField yRegister{ 1 };
    Binary::RawField pswRegister{ 1 };
    Binary::RawField spRegister{ 1 };
    Binary::RawField reserved{ 1 };

    Binary::RawFileStream fileStream{ "test.spc" };
    fileStream.Open(Binary::FileMode::Read);

    if (fileStream.IsOpen())
    {
        std::cout << "File opened successfully." << std::endl << std::endl;
        
        fileStream.Read(&headerID);
        fileStream.Read(&separator);
        fileStream.Read(&containsTag);
        fileStream.Read(&versionMinor);
        fileStream.Read(&pcRegister);
        fileStream.Read(&aRegister);
        fileStream.Read(&xRegister);
        fileStream.Read(&yRegister);
        fileStream.Read(&pswRegister);
        fileStream.Read(&spRegister);
        fileStream.Read(&reserved);
        fileStream.Close();

        PrintField("SPC Header ID", headerID.Value());
        PrintRawField("Separator", &separator);
        PrintField("Contains Tag", std::to_string(containsTag.Value()));
        PrintField("Version Minor", std::to_string(versionMinor.Value()));
        
        std::cout << std::endl;

        PrintRawField("PC Register", &pcRegister);
        PrintRawField("A Register", &aRegister);
        PrintRawField("X Register", &xRegister);
        PrintRawField("Y Register", &yRegister);
        PrintRawField("PSW Register", &pswRegister);
        PrintRawField("SP (lower byte)", &spRegister);
        PrintRawField("Reserved", &reserved);
    }
    else
    {
        std::cerr << "Unable to open file " << fileStream.FileName()
                  << std::endl << std::endl;
    }
    
    return 0;
}
