// Common.cpp - Defines common GUI utility functions.
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

#include "Common.h"

constexpr int labelWidth{ 125 };
constexpr int valueWidth{ 250 };

void AddToSizer(wxStaticText* label, wxStaticText* value, wxBoxSizer* sizer)
{
    // Set consistent label and value widths to ensure visual alignment.
    //label->SetMinSize(wxSize{ labelWidth, -1 });
    //value->SetMinSize(wxSize{ valueWidth, -1 });

    wxBoxSizer* valueSizer = new wxBoxSizer{ wxHORIZONTAL };
    valueSizer->Add(label, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    valueSizer->Add(value, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    sizer->Add(valueSizer, 0, wxALL | wxEXPAND);
}

void AddToSizer(wxStaticText* label, wxTextCtrl* textBox, wxBoxSizer* sizer)
{
    // Set a consistent label width when adding to the sizer to ensure the
    // corresponding text boxes are all aligned. 
    //label->SetMinSize(wxSize{ labelWidth, -1 });

    wxBoxSizer* textBoxSizer = new wxBoxSizer{ wxHORIZONTAL };
    textBoxSizer->Add(label, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    textBoxSizer->Add(textBox, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    sizer->Add(textBoxSizer, 1, wxALL | wxEXPAND);
}

wxString DetermineFieldValue(const Spc::Field& field)
{
    if (field.IsPresent())
    {
        return field.ToString();
    }
    else
    {
        return "-";
    }
}

wxString DetermineTagType(Spc::Header& header, Spc::Id666::Tag& tag)
{
    if (header.containsTag.ToUInt32() == Spc::headerContainsTag)
    {
        switch (tag.DetermineType())
        {
            case Spc::Id666::TagType::Text:
                return "Text";
            case Spc::Id666::TagType::Binary:
                return "Binary";
            case Spc::Id666::TagType::TextMixed:
                return "Mixed";
            default:
                return "-";
        }
    }
    else
    {
        return "-";
    }
}

wxString DetermineValue(const std::vector<wxString>& values)
{
    if (values.empty())
    {
        return "";
    }
    else if (values.size() == 1)
    {
        return values.at(0);
    }
    else
    {
        bool allSame = true;
        const wxString& firstValue = values.at(0);

        for (const wxString& value : values)
        {
            if (value != firstValue)
            {
                allSame = false;
                break;
            }
        }

        if (allSame)
        {
            return firstValue;
        }
        else
        {
            return "<multiple values>";
        }
    }
}

void CreateLabel(wxStaticText*& label, wxWindow* parent, 
                 std::vector<wxStaticText*>& labels, wxString text)
{
    label = new wxStaticText{ parent, wxID_ANY, text };
    labels.push_back(label);
}

void ResizeLabels(std::vector<wxStaticText*>& labels)
{
    int maxWidth = 0;

    for (wxStaticText* label : labels)
    {
        int width, height;

        label->GetTextExtent(label->GetLabelText(), &width, &height);
        maxWidth = std::max(maxWidth, width);
    }

    for (wxStaticText* label : labels)
    {
        label->SetMinSize(wxSize{ maxWidth, -1 });
    }
}