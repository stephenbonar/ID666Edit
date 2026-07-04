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

void AddToSizer(wxStaticText* label, wxStaticText* value, wxBoxSizer* sizer)
{
    // Set consistent label and value widths to ensure visual alignment.
    label->SetMinSize(wxSize{ labelWidth, -1 });
    value->SetMinSize(wxSize{ valueWidth, -1 });

    wxBoxSizer* valueSizer = new wxBoxSizer{ wxHORIZONTAL };
    valueSizer->Add(label, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    valueSizer->Add(value, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    sizer->Add(valueSizer, 0, wxALL | wxEXPAND);
}

void AddToSizer(wxStaticText* label, wxTextCtrl* textBox, wxBoxSizer* sizer)
{
    // Set a consistent label width when adding to the sizer to ensure the
    // corresponding text boxes are all aligned. 
    label->SetMinSize(wxSize{ labelWidth, -1 });
    textBox->SetMinSize(wxSize{ valueWidth, -1 });

    wxBoxSizer* textBoxSizer = new wxBoxSizer{ wxHORIZONTAL };
    textBoxSizer->Add(label, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    textBoxSizer->Add(textBox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    sizer->Add(textBoxSizer, 0, wxALL | wxEXPAND);
}

wxString DetermineFieldValue(Spc::Field* field)
{
    if (field->IsPresent())
    {
        return field->ToString();
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