// IncrementTrackWindow.cpp - Defines the IncrementTrackWindow class.
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

#include "IncrementTrackWindow.h"

IncrementTrackWindow::IncrementTrackWindow(
    wxWindow* parent, 
    std::vector<std::shared_ptr<Spc::File>>& selectedFiles) 
        : wxDialog(parent, wxID_ANY, "Increment Tr ack Numbers", 
                   wxDefaultPosition, wxSize(300, 150)),
          selectedFiles(selectedFiles)
{
    constexpr int mainBorderSize{ 10 };
    constexpr int buttonBorderSize{ 5 };

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxSizerFlags mainFlags = wxSizerFlags(noGrowthProportion);
    mainFlags.Expand().Border(wxALL, mainBorderSize);

    wxString text;
    text << "Increment the track numbers by the specified amount.\n"
         << "For instance, if you enter 2, each track number will be\n"
         << "increased by 2.\n";

    wxStaticText* instructionText = new wxStaticText(this, wxID_ANY, text);
    startTrackTextCtrl = new wxTextCtrl(this, wxID_ANY);
    mainSizer->Add(instructionText, mainFlags);
    mainSizer->Add(startTrackTextCtrl, mainFlags);

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxSizerFlags buttonFlags = wxSizerFlags(noGrowthProportion);
    buttonFlags.Border(wxALL, buttonBorderSize);
    
    wxButton* okButton = new wxButton(this, wxID_OK, "OK");
    okButton->Bind(wxEVT_BUTTON, &IncrementTrackWindow::OnOk, this);
    buttonSizer->Add(okButton, buttonFlags);

    wxButton* cancelButton = new wxButton(this, wxID_CANCEL, "Cancel");
    buttonSizer->Add(cancelButton, buttonFlags);

    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

    SetSizer(mainSizer);
    mainSizer->Fit(this);
}

void IncrementTrackWindow::OnOk(wxCommandEvent& event)
{
    long amount;

    if (!startTrackTextCtrl->GetValue().ToLong(&amount) || amount <= 0)
    {
        wxMessageBox("Please enter a valid positive integer", "Invalid Input",
                     wxOK | wxICON_ERROR);
        return;
    }

    for (size_t i = 0; i < selectedFiles.size(); ++i)
    {
        Spc::Id666::Tag tag = selectedFiles[i]->Tag();
        int32_t trackNumber = tag.OstTrack().ToInt32();
        tag.SetOstTrack(std::to_string(trackNumber + amount));
        selectedFiles[i]->SetTag(tag);
        selectedFiles[i]->Save();
    }

    EndModal(wxID_OK);
}