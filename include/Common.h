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
#include <wx/window.h>
#include <LibCppSpc.h>

/// @brief A proportion indicating no growth for sizer flags.
inline constexpr int noGrowthProportion{ 0 };

/// @brief A proportion indicating growth for sizer flags.
inline constexpr int growthProportion{ 1 };

/// @brief A proportion indicating triple growth for sizer flags.
inline constexpr int tripleGrowthProportion{ 3 };

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

/// @brief Determines the value to retrieve from the specified vector of values.
///
/// Use this function to determine the value to display in a text box when
/// one or more files are selected. If the vector is empty, none of the selected
/// files have a value and en empty string is returned. If the vector contains
/// exactly one value, then only one file is selected and that value is
/// returned as is. If the vector contains multiple values, then multiple files
/// are selected; if they are all the same, that value is returned, otherwise
/// as string indicating multiple values is returned.
///
/// @param values The vector of values to evaluate.
/// @return The string to display in the text box.
wxString GetCommonValue(const std::vector<wxString>& values);

/// @brief Gets the value of the specified field or a placeholder.
///
/// If the specified field is marked as being present in the SPC file, its
/// value is returned, otherwise a placeholder is returned.
///
/// @param field The field to evaluate.
/// @return The value if the field is present, otherwise a placeholder.
wxString GetValueOrPlaceholder(const Spc::Field& field);

/// @brief Gets the type of the tag in the specified header.
///
/// @param header The header to evaluate.
/// @param tag The tag to evaluate.
/// @return The type of the tag as a string, or "-" if no tag is present.
wxString GetTagType(const Spc::Header& header, const Spc::Id666::Tag& tag);

/// @brief Creates a static text label and adds it to the specified vector.
/// @param label A pointer to the static text label to create.
/// @param parent The parent window for the static text label.
/// @param labels The vector to which the label will be added.
/// @param text The text to display in the label.
void CreateLabel(wxStaticText*& label, wxWindow* parent, 
                 std::vector<wxStaticText*>& labels, wxString text);

/// @brief Resizes the specified static text labels to have a uniform width.
///
/// The function calculates the maximum width of the specified labels and sets
/// all of them to that width, ensuring that they are visually aligned.
///
/// @param labels The vector of static text labels to resize.
void ResizeLabels(std::vector<wxStaticText*>& labels);

#endif