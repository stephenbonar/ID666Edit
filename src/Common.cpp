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

void AddToSizer(wxStaticText* label, wxTextCtrl* textBox, wxBoxSizer* sizer)
{
    constexpr int borderSize{ 5 };

    wxSizerFlags textBoxFlags{ noGrowthProportion };
    textBoxFlags.Border(wxALL, borderSize);
    textBoxFlags.Align(wxALIGN_CENTER_VERTICAL);
    
    wxBoxSizer* textBoxSizer = new wxBoxSizer{ wxHORIZONTAL };
    textBoxSizer->Add(label, textBoxFlags);
    textBoxFlags.Proportion(growthProportion);
    textBoxSizer->Add(textBox, textBoxFlags);
    sizer->Add(textBoxSizer, growthProportion, wxALL | wxEXPAND);
}

wxString GetCommonValue(const std::vector<wxString>& values)
{
    constexpr int beginningIndex{ 0 };
    bool exactlyOneValue = values.size() == 1;

    if (values.empty())
    {
        return "";
    }
    else if (exactlyOneValue)
    {
        return values.at(beginningIndex);
    }
    else
    {
        bool allSame = true;
        const wxString& firstValue = values.at(beginningIndex);

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

wxString GetValueOrPlaceholder(const Spc::Field& field)
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

wxString GetTagType(const Spc::Header& header, const Spc::Id666::Tag& tag)
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

void CreateLabel(wxStaticText*& label, wxWindow* parent, 
                 std::vector<wxStaticText*>& labels, wxString text)
{
    label = new wxStaticText{ parent, wxID_ANY, text };
    labels.push_back(label);
}

void ResizeLabels(std::vector<wxStaticText*>& labels)
{
    constexpr int autoHeight{ -1 };
    int maxWidth{ 0 };

    for (wxStaticText* label : labels)
    {
        int width, height;

        label->GetTextExtent(label->GetLabelText(), &width, &height);
        maxWidth = std::max(maxWidth, width);
    }

    for (wxStaticText* label : labels)
    {
        label->SetMinSize(wxSize{ maxWidth, autoHeight });
    }
}