// ID666Edit.cpp - Defines the main GUI program class, ID666Edit.
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

#include "ID666Edit.h"
#include "Version.h"

bool ID666Edit::OnInit()
{
#if defined(__linux__)
    // Keep Linux desktop integration stable by using a consistent app id.
    SetAppName("id666edit");
    SetClassName("com.stephenbonar.id666edit");
    SetAppDisplayName("ID666Edit");
    wxInitAllImageHandlers();
#endif

    wxString versionString = wxString::Format("%s v%s %s",
                                              PROGRAM_NAME, 
                                              PROGRAM_VERSION, 
                                              PROGRAM_RELEASE);
    MainWindow *window = new MainWindow(versionString);
    window->Show();
    return true;
}

// Defines the appropriate entry point for the current platform.
wxIMPLEMENT_APP(ID666Edit);