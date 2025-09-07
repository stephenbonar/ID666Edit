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
#include <wx/filename.h>
#include <LibCppSpc.h>
#include "WidgetID.h"
#include "FileNameToTagWindow.h"

class MainWindow : public wxFrame
{
public:
    MainWindow();
private:
    wxPanel* panel;
    wxBoxSizer* leftColumnSizer;
    wxBoxSizer* rightColumnSizer;
    wxBoxSizer* headerColumn1Sizer;
    wxBoxSizer* headerColumn2Sizer;
    wxBoxSizer* tagColumn1Sizer;
    wxBoxSizer* tagColumn2Sizer;
    wxStaticBoxSizer* headerSizer;
    wxStaticBoxSizer* tagSizer;
    wxBoxSizer* panelSizer;
    wxBoxSizer* windowSizer;
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
    wxStaticText* dumperNameLabel;
    wxStaticText* commentsLabel;
    wxStaticText* dateDumpedLabel;
    wxStaticText* songLengthLabel;
    wxStaticText* fadeLengthLabel;
    wxStaticText* songArtistLabel;
    wxStaticText* defaultChannelStateLabel;
    wxStaticText* emulatorUsedLabel;
    wxStaticText* ostTitleLabel;
    wxStaticText* ostDiscLabel;
    wxStaticText* ostTrackLabel;
    wxStaticText* publisherNameLabel;
    wxStaticText* copyrightYearLabel;
    wxStaticText* introLengthLabel;
    wxStaticText* loopLengthLabel;
    wxStaticText* endLengthLabel;
    wxStaticText* mutedVoicesLabel;
    wxStaticText* loopTimesLabel;
    wxStaticText* preampLevelLabel;
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
    wxTextCtrl* dumperNameTextBox;
    wxTextCtrl* commentsTextBox;
    wxTextCtrl* dateDumpedTextBox;
    wxTextCtrl* songLengthTextBox;
    wxTextCtrl* fadeLengthTextBox;
    wxTextCtrl* songArtistTextBox;
    wxTextCtrl* defaultChannelStateTextBox;
    wxTextCtrl* emulatorUsedTextBox;
    wxTextCtrl* ostTitleTextBox;
    wxTextCtrl* ostDiscTextBox;
    wxTextCtrl* ostTrackTextBox;
    wxTextCtrl* publisherNameTextBox;
    wxTextCtrl* copyrightYearTextBox;
    wxTextCtrl* introLengthTextBox;
    wxTextCtrl* loopLengthTextBox;
    wxTextCtrl* endLengthTextBox;
    wxTextCtrl* mutedVoicesTextBox;
    wxTextCtrl* loopTimesTextBox;
    wxTextCtrl* preampLevelTextBox;
    
    std::vector<std::shared_ptr<Spc::File>> files;
    std::vector<std::shared_ptr<Spc::File>> selectedFiles;

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

    void UpdateHeaderLabels();

    void UpdateTagTextBoxes();

    void SetLabel(wxStaticText* label, std::vector<wxString>& values);

    void SetTextBox(wxTextCtrl* textBox, std::vector<wxString>& values);

    void OnExit(wxCommandEvent& event);

    void OnAbout(wxCommandEvent& event);

    void OnOpen(wxCommandEvent& event);

    void OnSave(wxCommandEvent& event);

    void OnFileNameToTag(wxCommandEvent& event);

    void OnTagToFileName(wxCommandEvent& event);

    void OnSelected(wxListEvent& event);
};

void AddToSizer(wxStaticText* label, wxStaticText* value, wxBoxSizer* sizer);

void AddToSizer(wxStaticText* label, wxTextCtrl* textBox, wxBoxSizer* sizer);

#endif