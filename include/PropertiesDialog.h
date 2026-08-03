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

#include <vector>
#include <wx/wx.h>
#include <LibCppSpc.h>
#include "Common.h"

/// @brief A dialog that displays the properties of selected SPC files.
class PropertiesDialog : public wxDialog
{
public:
    /// @brief Constructs a PropertiesDialog.
    /// @param parent The parent window.
    /// @param selectedFiles The selected SPC files to display properties for.
    PropertiesDialog(wxWindow* parent, 
                     std::vector<std::shared_ptr<Spc::File>> selectedFiles);
private:
    std::vector<std::shared_ptr<Spc::File>> selectedFiles;
    wxPanel* panel;
    wxBoxSizer* panelSizer;
    wxBoxSizer* windowSizer;
    wxBoxSizer* headerTagSizer;
    wxBoxSizer* headerRegisterSizer;
    wxBoxSizer* headerSpecialRegisterSizer;
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
    wxTextCtrl* idTextBox;
    wxTextCtrl* containsTagTextBox;
    wxTextCtrl* tagTypeTextBox;
    wxTextCtrl* versionMinorTextBox;
    wxTextCtrl* pcRegisterTextBox;
    wxTextCtrl* aRegisterTextBox;
    wxTextCtrl* xRegisterTextBox;
    wxTextCtrl* yRegisterTextBox;
    wxTextCtrl* pswRegisterTextBox;
    wxTextCtrl* spRegisterTextBox;
    std::vector<wxStaticText*> labels;

    /// @brief Creates the sizers for the dialog layout.
    void CreateSizers();

    /// @brief Creates the labels for the dialog.
    void CreateLabelText();

    /// @brief Creates the text boxes for the dialog.
    void CreateTextBoxes();

    /// @brief Creates the layout for the SPC file header static box.
    void CreateHeaderLayout();

    /// @brief Creates the layout for the dialog panel.
    void CreatePanelLayout();

    /// @brief Updates the controls in the header section for selected files.
    ///
    /// When the user selects files in the list view, this function updates 
    /// the header controls to reflect the information of the selected files.
    /// Values that are consistent across all selected files are displayed, 
    /// while inconsistent values are indicated with a placeholder.
    void UpdateHeaderSection();

    /// @brief Sets text box contents based on the values of selected files.
    /// @param textBox The text box to update.
    /// @param values The values retrieved from the selected files.
    void SetTextBox(wxTextCtrl* textBox, std::vector<wxString>& values);
};

#endif