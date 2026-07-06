// PropertiesDialog.cpp - Defines the PropertiesDialog class.
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

#include "PropertiesDialog.h"

PropertiesDialog::PropertiesDialog(wxWindow* parent, std::vector<std::shared_ptr<Spc::File>> selectedFiles) : 
    wxDialog(parent, wxID_ANY, "Properties", 
             wxDefaultPosition, wxSize(400, 300)),
    selectedFiles(selectedFiles)
{
    panel = new wxPanel(this);
    CreateSizers();
    CreateLabelText();
    CreateValueText();
    CreateHeaderLayout();
    CreatePanelLayout();
    UpdateHeaderSection();
}

void PropertiesDialog::CreateSizers()
{
    windowSizer = new wxBoxSizer{ wxVERTICAL };
    panelSizer = new wxBoxSizer{ wxVERTICAL };
    headerColumn1Sizer = new wxBoxSizer{ wxVERTICAL };
    headerColumn2Sizer = new wxBoxSizer{ wxVERTICAL };
    headerSizer = new wxStaticBoxSizer{  wxHORIZONTAL, panel, "Header" };
}

void PropertiesDialog::CreateLabelText()
{
    idLabel = new wxStaticText{ panel, wxID_ANY, "ID:" };
    containsTagLabel = new wxStaticText{ panel, wxID_ANY, "Contains Tag:" };
    tagTypeLabel = new wxStaticText{ panel, wxID_ANY, "Tag Type:" };
    versionMinorLabel = new wxStaticText{ panel, wxID_ANY, "Version Minor:" };
    pcRegisterLabel = new wxStaticText{ panel, wxID_ANY, "PC Register:" };
    aRegisterLabel = new wxStaticText{ panel, wxID_ANY, "A Register:" };
    xRegisterLabel = new wxStaticText{ panel, wxID_ANY, "X Register:" };
    yRegisterLabel = new wxStaticText{ panel, wxID_ANY, "Y Register:" };
    pswRegisterLabel = new wxStaticText{ panel, wxID_ANY, "PSW Register:" };
    spRegisterLabel = new wxStaticText{ panel, wxID_ANY, "SP Register:" };
}

void PropertiesDialog::CreateValueText()
{
    id = new wxStaticText{ panel, wxID_ANY, "-" };
    containsTag = new wxStaticText{ panel, wxID_ANY, "-" };
    tagType = new wxStaticText{ panel, wxID_ANY, "-" };
    versionMinor = new wxStaticText{ panel, wxID_ANY, "-" };
    pcRegister = new wxStaticText{ panel, wxID_ANY, "-" };
    aRegister = new wxStaticText{ panel, wxID_ANY, "-" };
    xRegister = new wxStaticText{ panel, wxID_ANY, "-" };
    yRegister = new wxStaticText{ panel, wxID_ANY, "-" };
    pswRegister = new wxStaticText{ panel, wxID_ANY, "-" };
    spRegister = new wxStaticText{ panel, wxID_ANY, "-" };
}

void PropertiesDialog::CreateHeaderLayout()
{
    AddToSizer(idLabel, id, headerColumn1Sizer);
    AddToSizer(containsTagLabel, containsTag, headerColumn1Sizer);
    AddToSizer(tagTypeLabel, tagType, headerColumn1Sizer);
    AddToSizer(versionMinorLabel, versionMinor, headerColumn1Sizer);
    AddToSizer(pcRegisterLabel, pcRegister, headerColumn2Sizer);
    AddToSizer(aRegisterLabel, aRegister, headerColumn2Sizer);
    AddToSizer(xRegisterLabel, xRegister, headerColumn2Sizer);
    AddToSizer(yRegisterLabel, yRegister, headerColumn2Sizer);
    AddToSizer(pswRegisterLabel, pswRegister, headerColumn2Sizer);
    AddToSizer(spRegisterLabel, spRegister, headerColumn2Sizer);
    headerSizer->Add(headerColumn1Sizer, 0, wxALL | wxEXPAND);
    headerSizer->Add(headerColumn2Sizer, 0, wxALL | wxEXPAND);
}

void PropertiesDialog::CreatePanelLayout()
{
    panelSizer->Add(headerSizer, 1, wxALL | wxEXPAND);
    panel->SetSizer(panelSizer);
    windowSizer->Add(panel, 1, wxEXPAND | wxALL);

    // Because the status bar isn't included in layout calculations, we need
    // to add the status bar height to the spacer to avoid veritcal cutoff.
    //int statusBarHeight = GetStatusBar()->GetSize().GetHeight();
    //rightColumnSizer->AddSpacer(statusBarHeight);

    SetSizerAndFit(windowSizer);

    // Ensure the file list view column fills the entire width.
    //int listViewWidth = fileListView->GetSize().GetWidth();
    //fileListView->SetColumnWidth(0, listViewWidth);
}

void PropertiesDialog::UpdateHeaderSection()
{
    std::vector<wxString> idValues;
    std::vector<wxString> headerContainsTagValues;
    std::vector<wxString> tagTypeValues;
    std::vector<wxString> versionMinorValues;
    std::vector<wxString> pcRegisterValues;
    std::vector<wxString> aRegisterValues;
    std::vector<wxString> xRegisterValues;
    std::vector<wxString> yRegisterValues;
    std::vector<wxString> pswRegisterValues;
    std::vector<wxString> spRegisterValues;

    for (std::shared_ptr<Spc::File> file : selectedFiles)
    {
        Spc::Header header = file->Header();
        Spc::Id666::Tag tag = file->Tag();
        idValues.push_back(wxString{ header.id.ToString() });

        wxString tagType = DetermineTagType(header, tag);

        if (tagType == "-")
        {
            headerContainsTagValues.push_back("False");
            tagTypeValues.push_back("-");
        }
        else
        {
            headerContainsTagValues.push_back("True");
            tagTypeValues.push_back(tagType);
        }

        versionMinorValues.push_back(header.versionMinor.ToString());
        pcRegisterValues.push_back(header.pcRegister.ToString());
        aRegisterValues.push_back(header.aRegister.ToString());
        xRegisterValues.push_back(header.xRegister.ToString());
        yRegisterValues.push_back(header.yRegister.ToString());
        pswRegisterValues.push_back(header.pswRegister.ToString());
        spRegisterValues.push_back(header.spRegister.ToString());
    }

    SetStaticText(id, idValues);
    SetStaticText(containsTag, headerContainsTagValues);
    SetStaticText(tagType, tagTypeValues);
    SetStaticText(versionMinor, versionMinorValues);
    SetStaticText(pcRegister, pcRegisterValues);
    SetStaticText(aRegister, aRegisterValues);
    SetStaticText(xRegister, xRegisterValues);
    SetStaticText(yRegister, yRegisterValues);
    SetStaticText(pswRegister, pswRegisterValues);
    SetStaticText(spRegister, spRegisterValues);
}

void PropertiesDialog::SetStaticText(wxStaticText* text, 
                               std::vector<wxString>& values)
{
    if (values.empty())
    {
        text->SetLabel("-");
    }
    else
    {
        text->SetLabel(DetermineValue(values));
    }
}
