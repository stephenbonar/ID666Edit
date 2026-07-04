// MainWindow.cpp - Defines the MainWindow class.
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

#include "MainWindow.h"

constexpr int labelWidth{ 150 };
constexpr int valueWidth{ 250 };
 
MainWindow::MainWindow(wxString version) : 
    wxFrame(nullptr, wxID_ANY, version), version{ version }
{
    SetIcon(wxICON(IDI_MAIN));
    panel = new wxPanel(this);
    CreateStatusBar();
    CreateMenuBar();
    CreateSizers();
    CreateLabelText();
    CreateValueText();
    CreateTextBoxes();
    CreateFileListView();
    //CreateHeaderLayout();
    CreateTagLayout();
    CreatePanelLayout();
    BindEvents();
    SetStatusText("Ready");
}

void MainWindow::CreateMenuBar()
{
    fileMenu = new wxMenu;
    fileMenu->Append(WidgetID::Open, "&Open...\tCtrl+O", "Open .spc files");
    fileMenu->Append(WidgetID::Save, "&Save...\tCtrl+S", 
                     "Saves changes to the .spc files");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt+F4", "Exit the application");

    editMenu = new wxMenu;
    editMenu->Append(WidgetID::FileNameToTag, "Filename to Tag...\tCtrl+F", 
                     "Set tag values from filename using a pattern");
    editMenu->Append(WidgetID::TagToFileName, "Tag to Filename...\tCtrl+T", 
                     "Set filename from tag values using a pattern");
    editMenu->AppendSeparator();
    editMenu->Append(WidgetID::IncrementTrack, 
                     "Increment Track Numbers...\tCtrl+I", 
                     "Increment OST track numbers by a specified amount");

    helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT, "&About\tF1", 
                     "Show information about the application");

    menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(editMenu, "&Edit");
    menuBar->Append(helpMenu, "&Help");
    menuBar->Enable(WidgetID::Save, false);

    SetMenuBar(menuBar);
}

void MainWindow::CreateSizers()
{
    leftColumnSizer = new wxBoxSizer{ wxVERTICAL };
    rightColumnSizer = new wxBoxSizer{ wxVERTICAL };
    //headerColumn1Sizer = new wxBoxSizer{ wxVERTICAL };
    //headerColumn2Sizer = new wxBoxSizer{ wxVERTICAL };
    tagColumn1Sizer = new wxBoxSizer{ wxVERTICAL };
    tagColumn2Sizer = new wxBoxSizer{ wxVERTICAL };
    //headerSizer = new wxStaticBoxSizer{  wxHORIZONTAL, panel, "Header" };
    tagSizer = new wxStaticBoxSizer{ wxHORIZONTAL, panel, "Tag" };
    panelSizer = new wxBoxSizer{ wxHORIZONTAL };
    windowSizer = new wxBoxSizer{ wxVERTICAL };
}

void MainWindow::CreateLabelText()
{
    //idLabel = new wxStaticText{ panel, wxID_ANY, "ID:" };
    //containsTagLabel = new wxStaticText{ panel, wxID_ANY, "Contains Tag:" };
    tagTypeLabel = new wxStaticText{ panel, wxID_ANY, "Tag Type:" };
    //versionMinorLabel = new wxStaticText{ panel, wxID_ANY, "Version Minor:" };
    //pcRegisterLabel = new wxStaticText{ panel, wxID_ANY, "PC Register:" };
    //aRegisterLabel = new wxStaticText{ panel, wxID_ANY, "A Register:" };
    //xRegisterLabel = new wxStaticText{ panel, wxID_ANY, "X Register:" };
    //yRegisterLabel = new wxStaticText{ panel, wxID_ANY, "Y Register:" };
    //pswRegisterLabel = new wxStaticText{ panel, wxID_ANY, "PSW Register:" };
    //spRegisterLabel = new wxStaticText{ panel, wxID_ANY, "SP Register:" };
    songTitleLabel = new wxStaticText{ panel, wxID_ANY, "Song Title" };
    gameTitleLabel = new wxStaticText{ panel, wxID_ANY, "Game Title" };
    dumperNameLabel = new wxStaticText{ panel, wxID_ANY, "Dumper Name" };
    commentsLabel = new wxStaticText{ panel, wxID_ANY, "Comments" };
    dateDumpedLabel = new wxStaticText{ panel, wxID_ANY, "Date Dumped" };
    songLengthLabel = new wxStaticText{ panel, wxID_ANY, "Song Length (sec)" };
    fadeLengthLabel = new wxStaticText{ panel, wxID_ANY, "Fade Length (ms)" };
    songArtistLabel = new wxStaticText{ panel, wxID_ANY, "Song Artist" };
    defaultChannelStateLabel = new wxStaticText
    { 
        panel, wxID_ANY, "Default Channel State" 
    };
    emulatorUsedLabel = new wxStaticText{ panel, wxID_ANY, "Emulator Used" };
    ostTitleLabel = new wxStaticText{ panel, wxID_ANY, "OST Title" };
    ostDiscLabel = new wxStaticText{ panel, wxID_ANY, "OST Disc" };
    ostTrackLabel = new wxStaticText{ panel, wxID_ANY, "OST Track" };
    publisherNameLabel = new wxStaticText{ panel, wxID_ANY, "Publisher Name" };
    copyrightYearLabel = new wxStaticText{ panel, wxID_ANY, "Copyright Year" };
    introLengthLabel = new wxStaticText
    {
        panel, wxID_ANY, "Intro Length (ticks)" 
    };
    loopLengthLabel = new wxStaticText
    {
        panel, wxID_ANY, "Loop Length (ticks)" 
    };
    endLengthLabel = new wxStaticText
    {
        panel, wxID_ANY, "End Length (ticks)" 
    };
    mutedVoicesLabel = new wxStaticText{ panel, wxID_ANY, "Muted Voices" };
    loopTimesLabel = new wxStaticText{ panel, wxID_ANY, "Loop Times" };
    preampLevelLabel = new wxStaticText{ panel, wxID_ANY, "Preamp Level" };
}

void MainWindow::CreateValueText()
{
    //id = new wxStaticText{ panel, wxID_ANY, "-" };
    //containsTag = new wxStaticText{ panel, wxID_ANY, "-" };
    tagType = new wxStaticText{ panel, wxID_ANY, "-" };
    //versionMinor = new wxStaticText{ panel, wxID_ANY, "-" };
    //pcRegister = new wxStaticText{ panel, wxID_ANY, "-" };
    //aRegister = new wxStaticText{ panel, wxID_ANY, "-" };
    //xRegister = new wxStaticText{ panel, wxID_ANY, "-" };
    //yRegister = new wxStaticText{ panel, wxID_ANY, "-" };
    //pswRegister = new wxStaticText{ panel, wxID_ANY, "-" };
    //spRegister = new wxStaticText{ panel, wxID_ANY, "-" };
}

void MainWindow::CreateTextBoxes()
{
    songTitleTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    gameTitleTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    dumperNameTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    commentsTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    dateDumpedTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    songLengthTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    fadeLengthTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    songArtistTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    defaultChannelStateTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    emulatorUsedTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    ostTitleTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    ostDiscTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    ostTrackTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    publisherNameTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    copyrightYearTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    introLengthTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    loopLengthTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    endLengthTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    mutedVoicesTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    loopTimesTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
    preampLevelTextBox = new wxTextCtrl{ panel, wxID_ANY, "" };
}

void MainWindow::CreateFileListView()
{
    fileListView = new wxListView
    { 
        panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT 
    };

    fileListView->AppendColumn("Filename");
    fileListView->Bind(wxEVT_LIST_ITEM_SELECTED, &MainWindow::OnSelected, this);
}

/*
void MainWindow::CreateHeaderLayout()
{
    AddToSizer(idLabel, id, headerColumn1Sizer);
    AddToSizer(containsTagLabel, containsTag, headerColumn1Sizer);
    AddToSizer(tagTypeLabel, tagType, headerColumn1Sizer);
    AddToSizer(versionMinorLabel, versionMinor, headerColumn1Sizer);
    AddToSizer(pcRegisterLabel, pcRegister, headerColumn2Sizer);
    AddToSizer(aRegisterLabel, aRegister, headerColumn2Sizer);
    AddToSizer(xRegisterLabel, xRegister, headerColumn2Sizer);
    AddToSizer(yRegisterLabel, yRegister, headerColumn2Sizer);
    AddToSizer(pswRegisterLabel, pswRegister, headerColumn2Sizer);
    AddToSizer(spRegisterLabel, spRegister, headerColumn2Sizer);
    headerSizer->Add(headerColumn1Sizer, 0, wxALL | wxEXPAND);
    headerSizer->Add(headerColumn2Sizer, 0, wxALL | wxEXPAND);
}*/

void MainWindow::CreateTagLayout()
{
    AddToSizer(tagTypeLabel, tagType, tagColumn1Sizer);
    AddToSizer(songTitleLabel, songTitleTextBox, tagColumn1Sizer);
    AddToSizer(gameTitleLabel, gameTitleTextBox, tagColumn1Sizer);
    AddToSizer(dumperNameLabel, dumperNameTextBox, tagColumn1Sizer);
    AddToSizer(commentsLabel, commentsTextBox, tagColumn1Sizer);
    AddToSizer(dateDumpedLabel, dateDumpedTextBox, tagColumn1Sizer);
    AddToSizer(songLengthLabel, songLengthTextBox, tagColumn1Sizer);
    AddToSizer(fadeLengthLabel, fadeLengthTextBox, tagColumn1Sizer);
    AddToSizer(songArtistLabel, songArtistTextBox, tagColumn1Sizer);
    AddToSizer(defaultChannelStateLabel, defaultChannelStateTextBox, 
               tagColumn1Sizer);
    AddToSizer(emulatorUsedLabel, emulatorUsedTextBox, tagColumn1Sizer);
    AddToSizer(ostTitleLabel, ostTitleTextBox, tagColumn2Sizer);
    AddToSizer(ostDiscLabel, ostDiscTextBox, tagColumn2Sizer);
    AddToSizer(ostTrackLabel, ostTrackTextBox, tagColumn2Sizer);
    AddToSizer(publisherNameLabel, publisherNameTextBox, tagColumn2Sizer);
    AddToSizer(copyrightYearLabel, copyrightYearTextBox, tagColumn2Sizer);
    AddToSizer(introLengthLabel, introLengthTextBox, tagColumn2Sizer);
    AddToSizer(loopLengthLabel, loopLengthTextBox, tagColumn2Sizer);
    AddToSizer(endLengthLabel, endLengthTextBox, tagColumn2Sizer);
    AddToSizer(mutedVoicesLabel, mutedVoicesTextBox, tagColumn2Sizer);
    AddToSizer(loopTimesLabel, loopTimesTextBox, tagColumn2Sizer);
    AddToSizer(preampLevelLabel, preampLevelTextBox, tagColumn2Sizer);
    tagSizer->Add(tagColumn1Sizer, 0, wxALL | wxEXPAND);
    tagSizer->Add(tagColumn2Sizer, 0, wxALL | wxEXPAND);
}

void MainWindow::CreatePanelLayout()
{
    leftColumnSizer->Add(fileListView, 1, wxALL | wxEXPAND);
    //rightColumnSizer->Add(headerSizer, 0, wxALL | wxEXPAND, 5);
    rightColumnSizer->Add(tagSizer, 0, wxALL | wxEXPAND, 5);
    panelSizer->Add(leftColumnSizer, 1, wxALL | wxEXPAND);
    panelSizer->Add(rightColumnSizer, 3, wxALL | wxEXPAND);
    panel->SetSizer(panelSizer);
    windowSizer->Add(panel, 1, wxEXPAND | wxALL);

    // Because the status bar isn't included in layout calculations, we need
    // to add the status bar height to the spacer to avoid veritcal cutoff.
    int statusBarHeight = GetStatusBar()->GetSize().GetHeight();
    rightColumnSizer->AddSpacer(statusBarHeight);

    SetSizerAndFit(windowSizer);

    // Ensure the file list view column fills the entire width.
    int listViewWidth = fileListView->GetSize().GetWidth();
    fileListView->SetColumnWidth(0, listViewWidth);
}

void MainWindow::BindEvents()
{
    Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainWindow::OnOpen, this, WidgetID::Open);
    Bind(wxEVT_MENU, &MainWindow::OnSave, this, WidgetID::Save);
    Bind(wxEVT_MENU, &MainWindow::OnFileNameToTag, this, 
         WidgetID::FileNameToTag);
    Bind(wxEVT_MENU, &MainWindow::OnTagToFileName, this, 
         WidgetID::TagToFileName);
    Bind(wxEVT_MENU, &MainWindow::OnIncrementTrack, this, 
         WidgetID::IncrementTrack);
}

/*
void MainWindow::UpdateHeaderSection()
{
    std::vector<wxString> idValues;
    std::vector<wxString> headerContainsTagValues;
    std::vector<wxString> tagTypeValues;
    std::vector<wxString> versionMinorValues;
    std::vector<wxString> pcRegisterValues;
    std::vector<wxString> aRegisterValues;
    std::vector<wxString> xRegisterValues;
    std::vector<wxString> yRegisterValues;
    std::vector<wxString> pswRegisterValues;
    std::vector<wxString> spRegisterValues;

    for (std::shared_ptr<Spc::File> file : selectedFiles)
    {
        Spc::Header header = file->Header();
        Spc::Id666::Tag tag = file->Tag();
        idValues.push_back(wxString{ header.id.ToString() });

        wxString tagType = DetermineTagType(header, tag);

        if (tagType == "-")
        {
            headerContainsTagValues.push_back("False");
            tagTypeValues.push_back("-");
        }
        else
        {
            headerContainsTagValues.push_back("True");
            tagTypeValues.push_back(tagType);
        }

        versionMinorValues.push_back(header.versionMinor.ToString());
        pcRegisterValues.push_back(header.pcRegister.ToString());
        aRegisterValues.push_back(header.aRegister.ToString());
        xRegisterValues.push_back(header.xRegister.ToString());
        yRegisterValues.push_back(header.yRegister.ToString());
        pswRegisterValues.push_back(header.pswRegister.ToString());
        spRegisterValues.push_back(header.spRegister.ToString());
    }

    SetStaticText(id, idValues);
    SetStaticText(containsTag, headerContainsTagValues);
    SetStaticText(tagType, tagTypeValues);
    SetStaticText(versionMinor, versionMinorValues);
    SetStaticText(pcRegister, pcRegisterValues);
    SetStaticText(aRegister, aRegisterValues);
    SetStaticText(xRegister, xRegisterValues);
    SetStaticText(yRegister, yRegisterValues);
    SetStaticText(pswRegister, pswRegisterValues);
    SetStaticText(spRegister, spRegisterValues);
}
*/

void MainWindow::UpdateTagSection()
{
    std::vector<wxString> songTitleValues;
    std::vector<wxString> gameTitleValues;
    std::vector<wxString> dumperNameValues;
    std::vector<wxString> commentsValues;
    std::vector<wxString> dateDumpedValues;
    std::vector<wxString> songLengthValues;
    std::vector<wxString> fadeLengthValues;
    std::vector<wxString> songArtistValues;
    std::vector<wxString> defaultChannelStateValues;
    std::vector<wxString> emulatorUsedValues;
    std::vector<wxString> ostTitleValues;
    std::vector<wxString> ostDiscValues;
    std::vector<wxString> ostTrackValues;
    std::vector<wxString> publisherNameValues;
    std::vector<wxString> copyrightYearValues;
    std::vector<wxString> introLengthValues;
    std::vector<wxString> loopLengthValues;
    std::vector<wxString> endLengthValues;
    std::vector<wxString> mutedVoicesValues;
    std::vector<wxString> loopTimesValues;
    std::vector<wxString> preampLevelValues;

    for (std::shared_ptr<Spc::File> file : selectedFiles)
    {
        Spc::Id666::Tag tag = file->Tag();

        songTitleValues.push_back(DetermineFieldValue(&tag.SongTitle()));
        gameTitleValues.push_back(DetermineFieldValue(&tag.GameTitle()));
        dumperNameValues.push_back(DetermineFieldValue(&tag.DumperName()));
        commentsValues.push_back(DetermineFieldValue(&tag.Comments()));
        dateDumpedValues.push_back(DetermineFieldValue(&tag.DateDumped()));
        songLengthValues.push_back(DetermineFieldValue(&tag.SongLength()));
        fadeLengthValues.push_back(DetermineFieldValue(&tag.FadeLength()));
        songArtistValues.push_back(DetermineFieldValue(&tag.SongArtist()));
        defaultChannelStateValues.push_back(
            DetermineFieldValue(&tag.DefaultDisabledChannels()));
        emulatorUsedValues.push_back(DetermineFieldValue(&tag.EmulatorUsed()));
        ostTitleValues.push_back(DetermineFieldValue(&tag.OstTitle()));
        ostDiscValues.push_back(DetermineFieldValue(&tag.OstDisc()));
        ostTrackValues.push_back(DetermineFieldValue(&tag.OstTrack()));
        publisherNameValues.push_back(DetermineFieldValue(&tag.PublisherName()));
        copyrightYearValues.push_back(DetermineFieldValue(&tag.CopyrightYear()));
        introLengthValues.push_back(DetermineFieldValue(&tag.IntroLength()));
        loopLengthValues.push_back(DetermineFieldValue(&tag.LoopLength()));
        endLengthValues.push_back(DetermineFieldValue(&tag.EndLength()));
        mutedVoicesValues.push_back(DetermineFieldValue(&tag.MutedVoices()));
        loopTimesValues.push_back(DetermineFieldValue(&tag.LoopTimes()));
        preampLevelValues.push_back(DetermineFieldValue(&tag.PreampLevel()));
    }

    SetTextBox(songTitleTextBox, songTitleValues);
    SetTextBox(gameTitleTextBox, gameTitleValues);
    SetTextBox(dumperNameTextBox, dumperNameValues);
    SetTextBox(commentsTextBox, commentsValues);
    SetTextBox(dateDumpedTextBox, dateDumpedValues);
    SetTextBox(songLengthTextBox, songLengthValues);
    SetTextBox(fadeLengthTextBox, fadeLengthValues);
    SetTextBox(songArtistTextBox, songArtistValues);
    SetTextBox(defaultChannelStateTextBox, defaultChannelStateValues);
    SetTextBox(emulatorUsedTextBox, emulatorUsedValues);
    SetTextBox(ostTitleTextBox, ostTitleValues);
    SetTextBox(ostDiscTextBox, ostDiscValues);
    SetTextBox(ostTrackTextBox, ostTrackValues);
    SetTextBox(publisherNameTextBox, publisherNameValues);
    SetTextBox(copyrightYearTextBox, copyrightYearValues);
    SetTextBox(introLengthTextBox, introLengthValues);
    SetTextBox(loopLengthTextBox, loopLengthValues);
    SetTextBox(endLengthTextBox, endLengthValues);
    SetTextBox(mutedVoicesTextBox, mutedVoicesValues);
    SetTextBox(loopTimesTextBox, loopTimesValues);
    SetTextBox(preampLevelTextBox, preampLevelValues);
}

void MainWindow::UpdateStatusBar()
{
    wxString statusText;

    if (selectedFiles.empty())
    {
        statusText = "Ready";
    }
    else
    {
        std::vector<wxString> versionMinorValues;
        std::vector<wxString> headerContainsTagValues;
        std::vector<wxString> tagTypeValues;

        for (std::shared_ptr<Spc::File>& file : selectedFiles)
        {
            Spc::Header header = file->Header();
            Spc::Id666::Tag tag = file->Tag();
            wxString tagType = DetermineTagType(header, tag);

            versionMinorValues.push_back(header.versionMinor.ToString());

            if (tagType == "-")
            {
                headerContainsTagValues.push_back("False");
                tagTypeValues.push_back("-");
            }
            else
            {
                headerContainsTagValues.push_back("True");
                tagTypeValues.push_back(tagType);
            }
        }

        statusText = "";
        statusText << "SPC Format Version: v0." 
                   << DetermineValue(versionMinorValues) 
                   << " | Contains Tag: " 
                   << DetermineValue(headerContainsTagValues)
                   << " | Tag Type: " << DetermineValue(tagTypeValues);
        SetStatusText(statusText);
    }
}

wxString MainWindow::DetermineValue(const std::vector<wxString>& values)
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

void MainWindow::SetStaticText(wxStaticText* text, 
                               std::vector<wxString>& values)
{
    if (values.empty())
    {
        text->SetLabel("-");
    }
    else
    {
        text->SetLabel(DetermineValue(values));
    }
}

void MainWindow::SetTextBox(wxTextCtrl* textBox, std::vector<wxString>& values)
{
    if (values.empty())
    {
        textBox->Clear();
    }
    else
    {
        wxString value = DetermineValue(values);

        if (value == "-")
        {
            textBox->Clear();
        }
        else
        {
            textBox->SetValue(value);
        }
    }
}

void MainWindow::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MainWindow::OnAbout(wxCommandEvent& event)
{
    wxString aboutMessage;
    aboutMessage << version << "\n"
                 << PROGRAM_COPYRIGHT << "\n\n"
                 << "Licensed under the Apache License 2.0.\n\n"
                 << "This program includes:\n\n"
                 << "LibCppBinary - Apache License 2.0\n"
                 << "LibCppSpc - Apache License 2.0\n"
                 << "wxWidgets - wxWindows Library Licence\n\n"
                 << "See the licenses directory for full license texts.";

    wxMessageBox(aboutMessage, "About", wxOK | wxICON_INFORMATION, this);
}

void MainWindow::OnOpen(wxCommandEvent& event)
{
    // Allow multiple file selection by adding wxFD_MULTIPLE.
    wxFileDialog dialog(this, "Open SPC Files", wxEmptyString, wxEmptyString, 
                         "SPC Files (*.spc)|*.spc", wxFD_OPEN | wxFD_MULTIPLE);

    if (dialog.ShowModal() != wxID_OK) 
        return;

    files.clear();
    int itemIndex{ 0 };
    fileListView->DeleteAllItems();

    wxArrayString filePaths;
    dialog.GetPaths(filePaths);

    for (const wxString& path : filePaths)
    {
        auto file = std::make_shared<Spc::File>(path.ToStdString());
        file->Load();
        files.push_back(file);

        // Extract the file name from the path.
        wxFileName fileName{ path };
        wxString nameOnly = fileName.GetFullName();

        // Insert the file name into the fileListView.
        fileListView->InsertItem(itemIndex, nameOnly);
        itemIndex++;
    }
}

void MainWindow::OnSave(wxCommandEvent& event)
{
    for (std::shared_ptr<Spc::File> file : selectedFiles)
    {
        Spc::Id666::Tag tag = file->Tag();

        try
        {
            if (songTitleTextBox->GetValue() != "<multiple values>")
            {
                tag.SetSongTitle(songTitleTextBox->GetValue().ToStdString());
            }

            if (gameTitleTextBox->GetValue() != "<multiple values>")
            {
                tag.SetGameTitle(gameTitleTextBox->GetValue().ToStdString());
            }

            if (dumperNameTextBox->GetValue() != "<multiple values>")
            {
                tag.SetDumperName(dumperNameTextBox->GetValue().ToStdString());
            }

            if (commentsTextBox->GetValue() != "<multiple values>")
            {
                tag.SetComments(commentsTextBox->GetValue().ToStdString());
            }

            if (dateDumpedTextBox->GetValue() != "<multiple values>")
            {
                tag.SetDateDumped(dateDumpedTextBox->GetValue().ToStdString());
            }

            if (songLengthTextBox->GetValue() != "<multiple values>")
            {
                tag.SetSongLength(songLengthTextBox->GetValue().ToStdString());
            }

            if (fadeLengthTextBox->GetValue() != "<multiple values>")
            {
                tag.SetFadeLength(fadeLengthTextBox->GetValue().ToStdString());
            }

            if (songArtistTextBox->GetValue() != "<multiple values>")
            {
                tag.SetSongArtist(songArtistTextBox->GetValue().ToStdString());
            }

            if (defaultChannelStateTextBox->GetValue() != "<multiple values>")
            {
                tag.SetDefaultDisabledChannels(
                    defaultChannelStateTextBox->GetValue().ToStdString());
            }

            if (emulatorUsedTextBox->GetValue() != "<multiple values>")
            {
                tag.SetEmulatorUsed(
                    emulatorUsedTextBox->GetValue().ToStdString());
            }

            if (ostTitleTextBox->GetValue() != "<multiple values>")
            {
                tag.SetOstTitle(ostTitleTextBox->GetValue().ToStdString());
            }

            if (ostDiscTextBox->GetValue() != "<multiple values>")
            {
                tag.SetOstDisc(ostDiscTextBox->GetValue().ToStdString());
            }

            if (ostTrackTextBox->GetValue() != "<multiple values>")
            {
                tag.SetOstTrack(ostTrackTextBox->GetValue().ToStdString());
            }

            if (publisherNameTextBox->GetValue() != "<multiple values>")
            {
                tag.SetPublisherName(
                    publisherNameTextBox->GetValue().ToStdString());
            }

            if (copyrightYearTextBox->GetValue() != "<multiple values>")
            {
                tag.SetCopyrightYear(
                    copyrightYearTextBox->GetValue().ToStdString());
            }

            if (introLengthTextBox->GetValue() != "<multiple values>")
            {
                tag.SetIntroLength(introLengthTextBox->GetValue().ToStdString());
            }

            if (loopLengthTextBox->GetValue() != "<multiple values>")
            {
                tag.SetLoopLength(loopLengthTextBox->GetValue().ToStdString());
            }

            if (endLengthTextBox->GetValue() != "<multiple values>")
            {
                tag.SetEndLength(endLengthTextBox->GetValue().ToStdString());
            }

            if (mutedVoicesTextBox->GetValue() != "<multiple values>")
            {
                tag.SetMutedVoices(mutedVoicesTextBox->GetValue().ToStdString());
            }

            if (loopTimesTextBox->GetValue() != "<multiple values>")
            {
                tag.SetLoopTimes(loopTimesTextBox->GetValue().ToStdString());
            }

            if (preampLevelTextBox->GetValue() != "<multiple values>")
            {
                tag.SetPreampLevel(preampLevelTextBox->GetValue().ToStdString());
            }

            file->SetTag(tag);
            file->Save();
        }
        catch (const std::exception& ex)
        {
            wxMessageBox(ex.what(), "Error Saving File", wxOK | wxICON_ERROR);
            continue;
        }
    }
}

void MainWindow::OnFileNameToTag(wxCommandEvent& event)
{
    FileNameToTagDialog dialog{ this, selectedFiles };

    if (dialog.ShowModal() == wxID_OK)
    {
        UpdateTagSection();
    }
}
    
void MainWindow::OnTagToFileName(wxCommandEvent& event)
{
    TagToFileNameWindow dialog{ this, selectedFiles };

    if (dialog.ShowModal() == wxID_OK)
    {
        fileListView->DeleteAllItems();

        for (std::shared_ptr<Spc::File> file : files)
        {
            fileListView->InsertItem(0, file->Path());
        }
    }
}

void MainWindow::OnIncrementTrack(wxCommandEvent& event)
{
    IncrementTrackWindow dialog{ this, selectedFiles };

    if (dialog.ShowModal() == wxID_OK)
    {
        UpdateTagSection();
    }
}

void MainWindow::OnSelected(wxListEvent& event)
{
    //long selectedIndex = event.GetIndex();
    //std::shared_ptr<Spc::File> file = files.at(selectedIndex);

    selectedFiles.clear();
    long itemIndex{ -1 };

    while ((itemIndex = fileListView->GetNextItem(itemIndex, wxLIST_NEXT_ALL, 
                                                  wxLIST_STATE_SELECTED)) != -1)
    {
        selectedFiles.push_back(files.at(itemIndex));
    }

    menuBar->Enable(WidgetID::Save, !selectedFiles.empty());
    //UpdateHeaderSection();
    UpdateTagSection();
    UpdateStatusBar();
}
