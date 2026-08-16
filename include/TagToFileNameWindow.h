// TagToFileNameWindow.h - Declares the TagToFileNameWindow class.
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

#ifndef TAG_TO_FILE_NAME_WINDOW_H
#define TAG_TO_FILE_NAME_WINDOW_H

#include <vector>
#include <memory>
#include <wx/wx.h>
#include <LibCppSpc.h>
#include "Common.h"
#include "Version.h"

/// @brief A dialog for converting tag values to file names.
class TagToFileNameWindow : public wxDialog
{
public:
    /// @brief Constructs a TagToFileNameWindow dialog.
    /// @param parent The parent window.
    /// @param selectedFiles The files selected for conversion.
    TagToFileNameWindow(wxWindow* parent, 
                        std::vector<std::shared_ptr<Spc::File>>& selectedFiles);
private:
        wxTextCtrl* patternTextCtrl;
        std::vector<std::shared_ptr<Spc::File>>& selectedFiles;

        /// @brief Event handler for the OK button click event.
        /// @param event The event object.
        void OnOk(wxCommandEvent& event);
};

#endif