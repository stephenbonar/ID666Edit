// FileNameToTagWindow.cpp - Defines the FileNameToTagWindow class.
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

#include "FileNameToTagWindow.h"

FileNameToTagWindow::FileNameToTagWindow(
    wxWindow* parent,
    std::vector<std::shared_ptr<Spc::File>>& selectedFiles) : 
        selectedFiles{ selectedFiles },
        wxDialog(parent, wxID_ANY, "File Name to Tag", 
                 wxDefaultPosition, wxSize(400, 300))
{
    // Create a vertical box sizer to hold the dialog contents
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Add a static text label
    wxStaticText* instructionLabel = new wxStaticText
    {
        this, wxID_ANY, "Enter the pattern to extract tag values from file names:"
    };
    mainSizer->Add(instructionLabel, 0, wxALL | wxEXPAND, 10);

    // Add a text control for entering the pattern
    patternTextCtrl = new wxTextCtrl(this, wxID_ANY); // Store the text control as a member
    mainSizer->Add(patternTextCtrl, 0, wxALL | wxEXPAND, 10);

    // Add OK and Cancel buttons
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* okButton = new wxButton(this, wxID_OK, "OK");
    wxButton* cancelButton = new wxButton(this, wxID_CANCEL, "Cancel");
    buttonSizer->Add(okButton, 0, wxALL, 5);
    buttonSizer->Add(cancelButton, 0, wxALL, 5);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

    // Bind the OK button click event to a handler
    okButton->Bind(wxEVT_BUTTON, &FileNameToTagWindow::OnOk, this);

    // Set the sizer for the dialog
    SetSizer(mainSizer);
    mainSizer->Fit(this);
}

void FileNameToTagWindow::OnOk(wxCommandEvent& event)
{
    wxString pattern = patternTextCtrl->GetValue();

    for (std::shared_ptr<Spc::File> file : selectedFiles)
    {
        file->FileNameToTag(pattern.ToStdString());
        file->Save();
    }

    // Close the dialog with wxID_OK
    EndModal(wxID_OK);
}