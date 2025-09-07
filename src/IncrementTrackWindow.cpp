// IncrementTrackWindow.cpp - Defines the IncrementTrackWindow class.
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

#include "IncrementTrackWindow.h"

IncrementTrackWindow::IncrementTrackWindow(
    wxWindow* parent, 
    std::vector<std::shared_ptr<Spc::File>>& selectedFiles) 
    : wxDialog(parent, wxID_ANY, "Increment Track Numbers", wxDefaultPosition, wxSize(300, 150)),
      selectedFiles(selectedFiles)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* instructionText = new wxStaticText(this, wxID_ANY, "Enter increment amount");
    mainSizer->Add(instructionText, 0, wxALL | wxEXPAND, 10);

    startTrackTextCtrl = new wxTextCtrl(this, wxID_ANY);
    mainSizer->Add(startTrackTextCtrl, 0, wxALL | wxEXPAND, 10);

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* okButton = new wxButton(this, wxID_OK, "OK");
    okButton->Bind(wxEVT_BUTTON, &IncrementTrackWindow::OnOk, this);
    buttonSizer->Add(okButton, 0, wxALL, 5);

    wxButton* cancelButton = new wxButton(this, wxID_CANCEL, "Cancel");
    buttonSizer->Add(cancelButton, 0, wxALL, 5);

    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

    SetSizer(mainSizer);
    mainSizer->Fit(this);
}

void IncrementTrackWindow::OnOk(wxCommandEvent& event)
{
    long increment;

    if (!startTrackTextCtrl->GetValue().ToLong(&increment) || increment <= 0)
    {
        wxMessageBox("Please enter a valid positive integer for the increment amount.", "Invalid Input", wxOK | wxICON_ERROR);
        return;
    }

    for (size_t i = 0; i < selectedFiles.size(); ++i)
    {
        increment += selectedFiles[i]->OstTrack().Value();
        selectedFiles[i]->SetOstTrack(std::to_string(increment));
        selectedFiles[i]->Save();
    }

    EndModal(wxID_OK);
}