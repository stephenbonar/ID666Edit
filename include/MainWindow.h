// MainWindow.h - Declares the MainWindow class.
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

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <vector>
#include <memory>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/filename.h>
#include <LibCppSpc.h>
#include "WidgetID.h"
#include "FileNameToTagDialog.h"
#include "TagToFileNameWindow.h"
#include "IncrementTrackWindow.h"
#include "Version.h"
#include "Common.h"
#include "PropertiesDialog.h"

/// @brief The main window of the application.
class MainWindow : public wxFrame
{
public:
    /// @brief Constructs the main window.
    /// @param version The version string to display in the window.
    MainWindow(wxString version);
private:
    wxMenuBar* menuBar;
    wxMenu* fileMenu;
    wxMenu* editMenu;
    wxMenu* viewMenu;
    wxMenu* helpMenu;
    wxPanel* panel;
    wxBoxSizer* leftColumnSizer;
    wxBoxSizer* rightColumnSizer;
    wxBoxSizer* rightColumnTopSizer;
    wxBoxSizer* rightColumnBottomSizer;
    wxBoxSizer* panelSizer;
    wxBoxSizer* windowSizer;
    wxBoxSizer* ostHorizontalSizer;
    wxBoxSizer* timingHorizontalSizer1;
    wxBoxSizer* timingHorizontalSizer2;
    wxBoxSizer* outputHorizontalSizer;
    wxBoxSizer* dumpInfoHorizontalSizer;
    wxBoxSizer* buttonSizer;
    wxStaticBoxSizer* tagGeneralInfoSizer;
    wxStaticBoxSizer* tagDumpInfoSizer;
    wxStaticBoxSizer* tagOstInfoSizer;
    wxStaticBoxSizer* tagTimingSizer;
    wxStaticBoxSizer* tagAudioChannelsSizer;
    wxListView* fileListView;
    wxStaticText* songTitleLabel;
    wxStaticText* gameTitleLabel;
    wxStaticText* dumperNameLabel;
    wxStaticText* commentsLabel;
    wxStaticText* dateDumpedLabel;
    wxStaticText* songLengthLabel;
    wxStaticText* fadeLengthLabel;
    wxStaticText* songArtistLabel;
    wxStaticText* defaultDisabledChannelsLabel;
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
    wxTextCtrl* songTitleTextBox;
    wxTextCtrl* gameTitleTextBox;
    wxTextCtrl* dumperNameTextBox;
    wxTextCtrl* commentsTextBox;
    wxTextCtrl* dateDumpedTextBox;
    wxTextCtrl* songLengthTextBox;
    wxTextCtrl* fadeLengthTextBox;
    wxTextCtrl* songArtistTextBox;
    wxTextCtrl* defaultDisabledChannelsTextBox;
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
    wxButton* propertiesButton;
    wxButton* saveButton;
    wxString version;
    
    std::vector<std::shared_ptr<Spc::File>> files;
    std::vector<std::shared_ptr<Spc::File>> selectedFiles;
    std::vector<wxStaticText*> labels;

    /// @brief Creates the menu bar for the main window.
    void CreateMenuBar();

    /// @brief Creates the sizers for the main window layout.
    void CreateSizers();

    /// @brief Creates the static text objects that act as labels.
    void CreateLabels();

    /// @brief Creates the text boxes for user input.
    void CreateTextBoxes();

    /// @brief Creates the tool tips for the text boxes.
    void CreateToolTips();

    /// @brief Creates the buttons for user actions.
    void CreateButtons();

    /// @brief Creates the list view for selecting open files.
    void CreateFileListView();

    /// @brief Creates the layout for the tag section.
    void CreateTagLayout();

    /// @brief Creates the layout for the main panel.
    void CreatePanelLayout();

    /// @brief Binds the events to their respective handlers.
    void BindEvents();

    void UpdateEnabledControls();

    /// @brief Updates the controls in the tag section for selected files.
    ///
    /// When the user selects files in the list view, this function updates 
    /// the controls to reflect the tag information of the selected files.
    /// Values that are consistent across all selected files are displayed, 
    /// while inconsistent values are indicated with a placeholder.
    void UpdateTagSection();

    /// @brief Updates the status bar based on the selected files.
    ///
    /// When the user selects files in the list view, this function updates
    /// the status bar to show information about the selected files.
    void UpdateStatusBar();

    /// @brief Sets a text box's text based on the values of selected files.
    /// @param textBox The text box to update.
    /// @param values The values retrieved from the selected files.
    void SetTextBox(wxTextCtrl* textBox, std::vector<wxString>& values);

    /// @brief Click handler for the "Exit" menu item.
    /// @param event The event object.
    void OnExit(wxCommandEvent& event);

    /// @brief Click handler for the "About" menu item.
    /// @param event The event object.
    void OnAbout(wxCommandEvent& event);

    /// @brief Click handler for the "Open" menu item.
    /// @param event 
    void OnOpen(wxCommandEvent& event);

    /// @brief Click handler for the "Save" menu item.
    /// @param event The event object.
    void OnSave(wxCommandEvent& event);

    /// @brief Click handler for the "FileName to Tag" menu item.
    /// @param event The event object.
    void OnFileNameToTag(wxCommandEvent& event);

    /// @brief Click handler for the "Tag to FileName" menu item.
    /// @param event The event object.
    void OnTagToFileName(wxCommandEvent& event);

    /// @brief Click handler for the "Increment Track" menu item.
    /// @param event The event object.
    void OnIncrementTrack(wxCommandEvent& event);

    /// @brief Event handler for when the selection changes in the list view.
    /// @param event The event object.
    void OnSelectionChanged(wxListEvent& event);

    /*
    /// @brief Event handler for when a file is selected in the list view.
    /// @param event The event object.
    void OnSelected(wxListEvent& event);

    /// @brief Event handler for when a file is deselected in the list view.
    /// @param event The event object.
    void OnDeselected(wxListEvent& event);
    */

    /// @brief Event handler for when the properties button is clicked.
    /// @param event The event object.
    void OnProperties(wxCommandEvent& event);
};

#endif