// PropertiesDialog.h - Declares the PropertiesDialog class.
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

#ifndef PROPERTIES_DIALOG_H
#define PROPERTIES_DIALOG_H

#include <wx/wx.h>
#include <LibCppSpc.h>
#include "Common.h"

class PropertiesDialog : public wxDialog
{
public:
    PropertiesDialog(wxWindow* parent, Spc::File& file);
private:
    wxPanel* panel;
    wxBoxSizer* headerColumn1Sizer;
    wxBoxSizer* headerColumn2Sizer;
    wxStaticBoxSizer* headerSizer;
    wxStaticText* idLabel;
    wxStaticText* containsTagLabel;
    wxStaticText* tagTypeLabel;
    wxStaticText* versionMinorLabel;
    wxStaticText* pcRegisterLabel;
    wxStaticText* aRegisterLabel;
    wxStaticText* xRegisterLabel;
    wxStaticText* yRegisterLabel;
    wxStaticText* pswRegisterLabel;
    wxStaticText* spRegisterLabel;
    wxStaticText* id;
    wxStaticText* containsTag;
    wxStaticText* tagType;
    wxStaticText* versionMinor;
    wxStaticText* pcRegister;
    wxStaticText* aRegister;
    wxStaticText* xRegister;
    wxStaticText* yRegister;
    wxStaticText* pswRegister;
    wxStaticText* spRegister;

    void CreateSizers();

    void CreateLabelText();

    void CreateValueText();

    void CreateHeaderLayout();
}

#endif