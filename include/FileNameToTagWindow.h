// FileNameToTagWindow.h - Declares the FileNameToTagWindow class.
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

#ifndef FILE_NAME_TO_TAG_WINDOW_H
#define FILE_NAME_TO_TAG_WINDOW_H

#include <vector>
#include <memory>
#include <wx/wx.h>
#include <LibCppSpc.h>

class FileNameToTagWindow : public wxDialog
{
public:
    FileNameToTagWindow(
        wxWindow* parent, 
        std::vector<std::shared_ptr<Spc::File>>& selectedFiles);
private:
        wxTextCtrl* patternTextCtrl;
        std::vector<std::shared_ptr<Spc::File>>& selectedFiles;

        void OnOk(wxCommandEvent& event);
};

#endif