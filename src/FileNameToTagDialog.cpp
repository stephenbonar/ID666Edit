// FileNameToTagDialog.cpp - Defines the FileNameToTagDialog class.
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

#include "FileNameToTagDialog.h"

FileNameToTagDialog::FileNameToTagDialog(
    wxWindow* parent,
    std::vector<std::shared_ptr<Spc::File>>& selectedFiles) : 
        selectedFiles{ selectedFiles },
        wxDialog(parent, wxID_ANY, "Filename to Tag", 
                 wxDefaultPosition, wxSize(400, 300))
{
    constexpr int mainBorderSize{ 10 };
    constexpr int buttonBorderSize{ 5 };

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxSizerFlags mainFlags = wxSizerFlags(noGrowthProportion);
    mainFlags.Expand().Border(wxALL, mainBorderSize);

    wxString text;
    text << "Enter a filename pattern to extract tag values.\n\n"
         << "Example: ct-%track%.spc\n\n"
         << "This will extract the track number from ct-01.spc\n\n"
         << "Available placeholders:\n"
         << "%song% - The song title\n"
         << "%game% - The game title\n"
         << "%artist% - The song artist\n"
         << "%disc% - The disc number\n"
         << "%track% - The track number\n";

    wxStaticText* instructionLabel = new wxStaticText{ this, wxID_ANY, text };
    patternTextCtrl = new wxTextCtrl(this, wxID_ANY);
    mainSizer->Add(instructionLabel, mainFlags);
    mainSizer->Add(patternTextCtrl, mainFlags);

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxSizerFlags buttonFlags = wxSizerFlags(noGrowthProportion);
    buttonFlags.Border(wxALL, buttonBorderSize);

    wxButton* okButton = new wxButton(this, wxID_OK, "OK");
    wxButton* cancelButton = new wxButton(this, wxID_CANCEL, "Cancel");
    buttonSizer->Add(okButton, buttonFlags);
    buttonSizer->Add(cancelButton, buttonFlags);
    mainSizer->Add(buttonSizer, noGrowthProportion, wxALIGN_CENTER);

    okButton->Bind(wxEVT_BUTTON, &FileNameToTagDialog::OnOk, this);

    SetSizer(mainSizer);
    mainSizer->Fit(this);
}

void FileNameToTagDialog::OnOk(wxCommandEvent& event)
{
    wxString pattern = patternTextCtrl->GetValue();

    for (std::shared_ptr<Spc::File> file : selectedFiles)
    {
        file->FileNameToTag(pattern.ToStdString());
        file->Save();
    }

    EndModal(wxID_OK);
}