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
    wxListView* fileListView;
    wxStaticText* idLabel;
    wxStaticText* id;
    wxStaticText* containsTagLabel;
    wxStaticText* containsTag;
    wxStaticText* tagTypeLabel;
    wxStaticText* tagType;
    wxStaticText* versionMinorLabel;
    wxStaticText* versionMinor;
    wxStaticText* pcRegisterLabel;
    wxStaticText* pcRegister;
    wxStaticText* aRegisterLabel;
    wxStaticText* aRegister;
    wxStaticText* xRegisterLabel;
    wxStaticText* xRegister;
    wxStaticText* yRegisterLabel;
    wxStaticText* yRegister;
    wxStaticText* pswRegisterLabel;
    wxStaticText* pswRegister;
    wxStaticText* spRegisterLabel;
    wxStaticText* spRegister;
    std::vector<std::shared_ptr<Spc::File>> files;

    void OnExit(wxCommandEvent& event);

    void OnAbout(wxCommandEvent& event);

    void OnOpen(wxCommandEvent& event);

    void OnSave(wxCommandEvent& event);

    void OnSelected(wxListEvent& event);
};

#endif