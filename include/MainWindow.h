// MainWindow.h - Declares the MainWindow class.
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

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <vector>
#include <memory>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <LibCppSpc.h>
#include "WidgetID.h"

class MainWindow : public wxFrame
{
public:
    MainWindow();
private:
    wxPanel* panel;
    wxBoxSizer* leftColumnSizer;
    wxBoxSizer* rightColumnSizer;
    wxBoxSizer* headerLabelColumn1Sizer;
    wxBoxSizer* headerValueColumn1Sizer;
    wxBoxSizer* headerLabelColumn2Sizer;
    wxBoxSizer* headerValueColumn2Sizer;
    wxBoxSizer* tagLabelColumnSizer;
    wxBoxSizer* tagTextBoxColumnSizer;
    wxStaticBoxSizer* headerSizer;
    wxStaticBoxSizer* tagSizer;
    wxBoxSizer* panelSizer;
    wxListView* fileListView;
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
    wxStaticText* songTitleLabel;
    wxStaticText* gameTitleLabel;
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
    wxTextCtrl* songTitleTextBox;
    wxTextCtrl* gameTitleTextBox;
    std::vector<std::shared_ptr<Spc::File>> files;

    void CreateMenuBar();

    void CreateSizers();

    void CreateLabelText();

    void CreateValueText();

    void CreateTextBoxes();

    void CreateFileListView();

    void CreateHeaderLayout();

    void CreateTagLayout();

    void CreatePanelLayout();

    void BindEvents();

    void OnExit(wxCommandEvent& event);

    void OnAbout(wxCommandEvent& event);

    void OnOpen(wxCommandEvent& event);

    void OnSave(wxCommandEvent& event);

    void OnSelected(wxListEvent& event);
};

#endif