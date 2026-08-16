// TagToFileNameWindow.cpp - Defines the TagToFileNameWindow class.
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

#include "TagToFileNameWindow.h"

TagToFileNameWindow::TagToFileNameWindow(
    wxWindow* parent,
    std::vector<std::shared_ptr<Spc::File>>& selectedFiles) : 
        selectedFiles{ selectedFiles },
        wxDialog(parent, wxID_ANY, "Tag to Filename", 
                 wxDefaultPosition, wxSize(400, 300))
{
    constexpr int mainBorderSize{ 10 };
    constexpr int buttonBorderSize{ 5 };

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxString text;
    text << "Enter a filename pattern to populate the filename.\n\n"
         << "Example: %track% - %song%.spc\n\n"
         << "This will create a copy of the file with the new filename.\n\n"
         << "Available placeholders:\n"
         << "%song% - The song title\n"
         << "%game% - The game title\n"
         << "%artist% - The song artist\n"
         << "%disc% - The disc number\n"
         << "%track% - The track number\n";

    wxSizerFlags mainFlags = wxSizerFlags(noGrowthProportion).Expand();
    mainFlags.Border(wxALL, mainBorderSize);

    wxStaticText* instructionLabel = new wxStaticText{ this, wxID_ANY, text };
    mainSizer->Add(instructionLabel, mainFlags);

    patternTextCtrl = new wxTextCtrl(this, wxID_ANY);
    mainSizer->Add(patternTextCtrl, mainFlags);

    wxSizerFlags buttonSizerFlags = wxSizerFlags(noGrowthProportion);
    buttonSizerFlags.Border(wxALL, buttonBorderSize);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* okButton = new wxButton(this, wxID_OK, "OK");
    wxButton* cancelButton = new wxButton(this, wxID_CANCEL, "Cancel");
    buttonSizer->Add(okButton, buttonSizerFlags);
    buttonSizer->Add(cancelButton, buttonSizerFlags);
    mainSizer->Add(buttonSizer, noGrowthProportion, wxALIGN_CENTER);

    okButton->Bind(wxEVT_BUTTON, &TagToFileNameWindow::OnOk, this);

    SetSizer(mainSizer);
    mainSizer->Fit(this);
}

void TagToFileNameWindow::OnOk(wxCommandEvent& event)
{
    wxString pattern = patternTextCtrl->GetValue();

    int successCount{ 0 };

    for (std::shared_ptr<Spc::File> file : selectedFiles)
    {
        if (file->TagToFileName(pattern.ToStdString()))
        {
            file->Save();

            if (std::filesystem::exists(file->Path()))
            {
                ++successCount;
            }
        }
    }

    if (successCount == selectedFiles.size())
    {
        wxMessageBox("Newly renamed files created successfully.", 
                     PROGRAM_NAME, wxOK | wxICON_INFORMATION);
    }
    else
    {
        wxString text;
        text << "Failed to create some newly renamed files. Ensure the pattern"
             << " is valid and that\nthe resulting filenames will not contain"
             << " illegal characters on your platform.";
        wxMessageBox(text, PROGRAM_NAME, wxOK | wxICON_ERROR);
    }

    EndModal(wxID_OK);
}