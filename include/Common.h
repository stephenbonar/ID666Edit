// Common.h - Declares common GUI utility functions.
//
// Copyright (C) 2026 Stephen Bonar
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef COMMON_H
#define COMMON_H

#include <wx/wx.h>
#include <LibCppSpc.h>

/// @brief Adds specified label and value static text to the specified sizer.
///
/// Creates a horizontal sizer containing the label and value static text
/// objects to ensure they are visually aligned, and adds it to the specified
/// parent sizer.
///
/// @param label The static text object representing the value label.
/// @param value The static text object representing the value itself.
/// @param sizer The sizer to which the label and value will be added.
void AddToSizer(wxStaticText* label, wxStaticText* value, wxBoxSizer* sizer);

/// @brief Adds specified label and text box to the specified sizer.
///
/// Creates a horizontal sizer containing the label and text box
/// objects to ensure they are visually aligned, and adds it to the specified
/// parent sizer.
///
/// @param label The static text object representing the value label.
/// @param textBox The text box object representing the value itself.
/// @param sizer The sizer to which the label and text box will be added.
void AddToSizer(wxStaticText* label, wxTextCtrl* textBox, wxBoxSizer* sizer);

wxString DetermineValue(const std::vector<wxString>& values);

wxString DetermineFieldValue(Spc::Field* field);

wxString DetermineTagType(Spc::Header& header, Spc::Id666::Tag& tag);

#endif