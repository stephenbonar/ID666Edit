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
    {
        arguments.push_back(argv[i]);
    }

    Program program;
    return program.Run(arguments);
}
