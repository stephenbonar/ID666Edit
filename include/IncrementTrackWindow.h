// IncrementTrackWindow.h - Declares the IncrementTrackWindow class.
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

#ifndef INCREMENT_TRACK_WINDOW_H
#define INCREMENT_TRACK_WINDOW_H

#include <vector>
#include <memory>
#include <wx/wx.h>
#include <LibCppSpc.h>
#include "Common.h"

/// @brief A dialog window for incrementing the track number in ID666 tag data.
class IncrementTrackWindow : public wxDialog
{
public:
    /// @brief Constructs an IncrementTrackWindow.
    /// @param parent The parent window.
    /// @param selectedFiles A reference to the vector of selected files.
    IncrementTrackWindow(
        wxWindow* parent, 
        std::vector<std::shared_ptr<Spc::File>>& selectedFiles);
private:
        wxTextCtrl* startTrackTextCtrl;
        std::vector<std::shared_ptr<Spc::File>>& selectedFiles;

        /// @brief Click handler for the "OK" button.
        /// @param event The command event.
        void OnOk(wxCommandEvent& event);
};

#endif