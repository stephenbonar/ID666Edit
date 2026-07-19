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
             wxDefaultPosition, wxSize(600, 400)),
    selectedFiles(selectedFiles)
{
    panel = new wxPanel(this);
    CreateSizers();
    CreateLabelText();
    ResizeLabels(labels);
    CreateTextBoxes();
    CreateHeaderLayout();
    CreatePanelLayout();
    UpdateHeaderSection();
}

void PropertiesDialog::CreateSizers()
{
    windowSizer = new wxBoxSizer{ wxVERTICAL };
    panelSizer = new wxBoxSizer{ wxVERTICAL };
    headerTagSizer = new wxBoxSizer{ wxHORIZONTAL };
    headerRegisterSizer = new wxBoxSizer{ wxHORIZONTAL };
    headerSpecialRegisterSizer = new wxBoxSizer{ wxHORIZONTAL };
    headerSizer = new wxStaticBoxSizer{  wxVERTICAL, panel, "Header" };
}

void PropertiesDialog::CreateLabelText()
{
    CreateLabel(idLabel, panel, labels, "ID:");
    CreateLabel(containsTagLabel, panel, labels, "Contains Tag:");
    CreateLabel(tagTypeLabel, panel, labels, "Tag Type:");
    CreateLabel(versionMinorLabel, panel, labels, "Version Minor:");
    CreateLabel(pcRegisterLabel, panel, labels, "PC Register:");
    CreateLabel(aRegisterLabel, panel, labels, "A Register:");
    CreateLabel(xRegisterLabel, panel, labels, "X Register:");
    CreateLabel(yRegisterLabel, panel, labels, "Y Register:");
    CreateLabel(pswRegisterLabel, panel, labels, "PSW Register:");
    CreateLabel(spRegisterLabel, panel, labels, "SP Register:");
}

void PropertiesDialog::CreateTextBoxes()
{
    idTextBox = new wxTextCtrl(panel, wxID_ANY);
    containsTagTextBox = new wxTextCtrl(panel, wxID_ANY);
    tagTypeTextBox = new wxTextCtrl(panel, wxID_ANY);
    versionMinorTextBox = new wxTextCtrl(panel, wxID_ANY);
    pcRegisterTextBox = new wxTextCtrl(panel, wxID_ANY);
    aRegisterTextBox = new wxTextCtrl(panel, wxID_ANY);
    xRegisterTextBox = new wxTextCtrl(panel, wxID_ANY);
    yRegisterTextBox = new wxTextCtrl(panel, wxID_ANY);
    pswRegisterTextBox = new wxTextCtrl(panel, wxID_ANY);
    spRegisterTextBox = new wxTextCtrl(panel, wxID_ANY);

    idTextBox->Disable();
    containsTagTextBox->Disable();
    tagTypeTextBox->Disable();
    versionMinorTextBox->Disable();
    pcRegisterTextBox->Disable();
    aRegisterTextBox->Disable();
    xRegisterTextBox->Disable();
    yRegisterTextBox->Disable();
    pswRegisterTextBox->Disable();
    spRegisterTextBox->Disable();
}

void PropertiesDialog::CreateHeaderLayout()
{
    AddToSizer(idLabel, idTextBox, headerSizer);

    AddToSizer(containsTagLabel, containsTagTextBox, headerTagSizer);
    AddToSizer(tagTypeLabel, tagTypeTextBox, headerTagSizer);
    AddToSizer(versionMinorLabel, versionMinorTextBox, headerTagSizer);
    headerSizer->Add(headerTagSizer, 0, wxALL | wxEXPAND);

    AddToSizer(pcRegisterLabel, pcRegisterTextBox, headerSpecialRegisterSizer);
    AddToSizer(spRegisterLabel, spRegisterTextBox, headerSpecialRegisterSizer);
    AddToSizer(pswRegisterLabel, pswRegisterTextBox, headerSpecialRegisterSizer);
    headerSizer->Add(headerSpecialRegisterSizer, 0, wxALL | wxEXPAND);
    
    AddToSizer(aRegisterLabel, aRegisterTextBox, headerRegisterSizer);
    AddToSizer(xRegisterLabel, xRegisterTextBox, headerRegisterSizer);
    AddToSizer(yRegisterLabel, yRegisterTextBox, headerRegisterSizer);
    headerSizer->Add(headerRegisterSizer, 0, wxALL | wxEXPAND);
}

void PropertiesDialog::CreatePanelLayout()
{
    panelSizer->Add(headerSizer, 1, wxALL | wxEXPAND, 5);
    panel->SetSizer(panelSizer);
    windowSizer->Add(panel, 1, wxEXPAND | wxALL);

    SetSizerAndFit(windowSizer);
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

        wxString tagType = GetTagType(header, tag);

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

    SetTextBox(idTextBox, idValues);
    SetTextBox(containsTagTextBox, headerContainsTagValues);
    SetTextBox(tagTypeTextBox, tagTypeValues);
    SetTextBox(versionMinorTextBox, versionMinorValues);
    SetTextBox(pcRegisterTextBox, pcRegisterValues);
    SetTextBox(aRegisterTextBox, aRegisterValues);
    SetTextBox(xRegisterTextBox, xRegisterValues);
    SetTextBox(yRegisterTextBox, yRegisterValues);
    SetTextBox(pswRegisterTextBox, pswRegisterValues);
    SetTextBox(spRegisterTextBox, spRegisterValues);
}

void PropertiesDialog::SetTextBox(wxTextCtrl* textBox,
                                  std::vector<wxString>& values)
{
    if (values.empty())
    {
        textBox->Clear();
    }
    else
    {
        wxString value = GetCommonValue(values);

        if (value == "-")
        {
            textBox->Clear();
        }
        else
        {
            textBox->SetValue(value);
        }
    }
}
