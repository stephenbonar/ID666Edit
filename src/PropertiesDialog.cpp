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

PropertiesDialog::PropertiesDialog(wxWindow* parent, Spc::File& file) : 
    wxDialog(parent, wxID_ANY, "Properties", 
             wxDefaultPosition, wxSize(400, 300))
{
    panel = new wxPanel(this);
    CreateSizers();
    CreateLabelText();
    CreateValueText();
    CreateHeaderLayout();
}

void PropertiesDialog::CreateSizers()
{
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