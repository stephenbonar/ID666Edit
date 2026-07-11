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
 
MainWindow::MainWindow(wxString version) : 
    wxFrame(nullptr, wxID_ANY, version), version{ version }
{
#if defined(_WIN32)
    // On Windows, we need to set the application icon at runtime from the
    // resource file compiled into the application.
    SetIcon(wxICON(IDI_MAIN));
#endif

    panel = new wxPanel(this);
    CreateStatusBar();
    CreateMenuBar();
    CreateSizers();
    CreateLabels();
    ResizeLabels(labels);
    CreateTextBoxes();
    CreateButtons();
    CreateFileListView();
    CreateTagLayout();
    CreatePanelLayout();
    BindEvents();
    SetStatusText("Ready");
}

void MainWindow::CreateMenuBar()
{
    fileMenu = new wxMenu;
    fileMenu->Append(wxID_OPEN, "&Open...\tCtrl+O", "Open .spc files");
    fileMenu->Append(wxID_SAVE, "&Save...\tCtrl+S", 
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

    viewMenu = new wxMenu;
    viewMenu->Append(WidgetID::Properties, "Properties...\tCtrl+P", 
              "Show properties of the selected files");

    helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT, "&About\tF1", 
                     "Show information about the application");

    menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(editMenu, "&Edit");
    menuBar->Append(viewMenu, "&View");
    menuBar->Append(helpMenu, "&Help");
    menuBar->Enable(wxID_SAVE, false);
    menuBar->Enable(WidgetID::Properties, false);
    menuBar->Enable(WidgetID::FileNameToTag, false);
    menuBar->Enable(WidgetID::TagToFileName, false);
    menuBar->Enable(WidgetID::IncrementTrack, false);

    SetMenuBar(menuBar);
}

void MainWindow::CreateSizers()
{
    leftColumnSizer = new wxBoxSizer{ wxVERTICAL };
    rightColumnSizer = new wxBoxSizer{ wxVERTICAL };
    rightColumnTopSizer = new wxBoxSizer{ wxVERTICAL };
    rightColumnBottomSizer = new wxBoxSizer{ wxVERTICAL };
    ostHorizontalSizer = new wxBoxSizer{ wxHORIZONTAL };
    timingHorizontalSizer1 = new wxBoxSizer{ wxHORIZONTAL };
    timingHorizontalSizer2 = new wxBoxSizer{ wxHORIZONTAL };
    outputHorizontalSizer = new wxBoxSizer{ wxHORIZONTAL };
    dumpInfoHorizontalSizer = new wxBoxSizer{ wxHORIZONTAL };
    buttonSizer = new wxBoxSizer{ wxHORIZONTAL };
    tagGeneralInfoSizer = new wxStaticBoxSizer{ wxVERTICAL, panel, "General" };
    tagOstInfoSizer = new wxStaticBoxSizer{ wxVERTICAL, panel, "Original Soundtrack" };
    tagDumpInfoSizer = new wxStaticBoxSizer{ wxVERTICAL, panel, "Dump Info" };
    tagTimingSizer = new wxStaticBoxSizer{ wxVERTICAL, panel, "Timing" };
    tagAudioChannelsSizer = new wxStaticBoxSizer{ wxVERTICAL, panel, "Audio Channels" };
    panelSizer = new wxBoxSizer{ wxHORIZONTAL };
    windowSizer = new wxBoxSizer{ wxVERTICAL };
}

void MainWindow::CreateLabels()
{
    wxStaticBox* tagGeneralInfoBox = tagGeneralInfoSizer->GetStaticBox();
    CreateLabel(songTitleLabel, tagGeneralInfoBox, labels, "Song Title");
    CreateLabel(gameTitleLabel, tagGeneralInfoBox, labels, "Game Title");
    CreateLabel(songArtistLabel, tagGeneralInfoBox, labels, "Song Artist");
    CreateLabel(commentsLabel, tagGeneralInfoBox, labels, "Comments");

    wxStaticBox* tagOstInfoBox = tagOstInfoSizer->GetStaticBox();
    CreateLabel(ostTitleLabel, tagOstInfoBox, labels, "OST Title");
    CreateLabel(ostDiscLabel, tagOstInfoBox, labels, "OST Disc");
    CreateLabel(ostTrackLabel, tagOstInfoBox, labels, "OST Track");
    CreateLabel(publisherNameLabel, tagOstInfoBox, labels, "Publisher Name");
    CreateLabel(copyrightYearLabel, tagOstInfoBox, labels, "Copyright Year");

    wxStaticBox* tagDumpInfoBox = tagDumpInfoSizer->GetStaticBox();
    CreateLabel(dumperNameLabel, tagDumpInfoBox, labels, "Dumper Name");
    CreateLabel(dateDumpedLabel, tagDumpInfoBox, labels, "Date Dumped");
    CreateLabel(emulatorUsedLabel, tagDumpInfoBox, labels, "Emulator Used");

    wxStaticBox* tagTimingBox = tagTimingSizer->GetStaticBox();
    CreateLabel(songLengthLabel, tagTimingBox, labels, "Song Length (sec)");
    CreateLabel(fadeLengthLabel, tagTimingBox, labels, "Fade Length (ms)");
    CreateLabel(introLengthLabel, tagTimingBox, labels, "Intro Length (ticks)");
    CreateLabel(loopLengthLabel, tagTimingBox, labels, "Loop Length (ticks)");
    CreateLabel(endLengthLabel, tagTimingBox, labels, "End Length (ticks)");
    CreateLabel(loopTimesLabel, tagTimingBox, labels, "Loop Times");

    wxStaticBox* tagAudioChannelsBox = tagAudioChannelsSizer->GetStaticBox();
    CreateLabel(defaultDisabledChannelsLabel, tagAudioChannelsBox, 
                labels, "Disabled by Default");
    CreateLabel(mutedVoicesLabel, tagAudioChannelsBox, labels, "Muted");
    CreateLabel(preampLevelLabel, tagAudioChannelsBox, labels, "Preamp Level");
}

void MainWindow::CreateTextBoxes()
{
    wxStaticBox* tagGeneralInfoBox = tagGeneralInfoSizer->GetStaticBox();
    songTitleTextBox = new wxTextCtrl{ tagGeneralInfoBox, wxID_ANY, "" };
    gameTitleTextBox = new wxTextCtrl{ tagGeneralInfoBox, wxID_ANY, "" };
    songArtistTextBox = new wxTextCtrl{ tagGeneralInfoBox, wxID_ANY, "" };
    commentsTextBox = new wxTextCtrl{ tagGeneralInfoBox, wxID_ANY, "" };

    wxStaticBox* tagOstInfoBox = tagOstInfoSizer->GetStaticBox();
    ostTitleTextBox = new wxTextCtrl{ tagOstInfoBox, wxID_ANY, "" };
    ostDiscTextBox = new wxTextCtrl{ tagOstInfoBox, wxID_ANY, "" };
    ostTrackTextBox = new wxTextCtrl{ tagOstInfoBox, wxID_ANY, "" };
    publisherNameTextBox = new wxTextCtrl{ tagOstInfoBox, wxID_ANY, "" };
    copyrightYearTextBox = new wxTextCtrl{ tagOstInfoBox, wxID_ANY, "" };
    
    wxStaticBox* tagDumpInfoBox = tagDumpInfoSizer->GetStaticBox();
    dumperNameTextBox = new wxTextCtrl{ tagDumpInfoBox, wxID_ANY, "" };
    dateDumpedTextBox = new wxTextCtrl{ tagDumpInfoBox, wxID_ANY, "" };
    emulatorUsedTextBox = new wxTextCtrl{ tagDumpInfoBox, wxID_ANY, "" };
    
    wxStaticBox* tagTimingBox = tagTimingSizer->GetStaticBox();
    songLengthTextBox = new wxTextCtrl{ tagTimingBox, wxID_ANY, "" };
    fadeLengthTextBox = new wxTextCtrl{ tagTimingBox, wxID_ANY, "" };
    introLengthTextBox = new wxTextCtrl{ tagTimingBox, wxID_ANY, "" };
    loopLengthTextBox = new wxTextCtrl{ tagTimingBox, wxID_ANY, "" };
    endLengthTextBox = new wxTextCtrl{ tagTimingBox, wxID_ANY, "" };
    loopTimesTextBox = new wxTextCtrl{ tagTimingBox, wxID_ANY, "" };
    
    wxStaticBox* tagAudioChannelsBox = tagAudioChannelsSizer->GetStaticBox();
    defaultDisabledChannelsTextBox = new wxTextCtrl{ tagAudioChannelsBox, wxID_ANY, "" };
    mutedVoicesTextBox = new wxTextCtrl{ tagAudioChannelsBox, wxID_ANY, "" };
    preampLevelTextBox = new wxTextCtrl{ tagAudioChannelsBox, wxID_ANY, "" };
}

void MainWindow::CreateButtons()
{
    propertiesButton = new wxButton{ panel, WidgetID::Properties, "Properties" };
    saveButton = new wxButton{ panel, wxID_SAVE, "Save" };
    propertiesButton->Enable(false);
    saveButton->Enable(false);
    propertiesButton->Bind(wxEVT_BUTTON, &MainWindow::OnProperties, this);
    saveButton->Bind(wxEVT_BUTTON, &MainWindow::OnSave, this);
}

void MainWindow::CreateFileListView()
{
    fileListView = new wxListView
    { 
        panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT 
    };

    fileListView->AppendColumn("Filename");
    fileListView->Bind(wxEVT_LIST_ITEM_SELECTED, &MainWindow::OnSelectionChanged, this);
    fileListView->Bind(wxEVT_LIST_ITEM_DESELECTED, &MainWindow::OnSelectionChanged, this);
}

void MainWindow::CreateTagLayout()
{
    AddToSizer(songTitleLabel, songTitleTextBox, tagGeneralInfoSizer);
    AddToSizer(gameTitleLabel, gameTitleTextBox, tagGeneralInfoSizer);
    AddToSizer(songArtistLabel, songArtistTextBox, tagGeneralInfoSizer);
    AddToSizer(commentsLabel, commentsTextBox, tagGeneralInfoSizer);

    AddToSizer(ostTitleLabel, ostTitleTextBox, tagOstInfoSizer);
    AddToSizer(publisherNameLabel, publisherNameTextBox, tagOstInfoSizer);
    AddToSizer(ostDiscLabel, ostDiscTextBox, ostHorizontalSizer);
    AddToSizer(ostTrackLabel, ostTrackTextBox, ostHorizontalSizer);
    AddToSizer(copyrightYearLabel, copyrightYearTextBox, ostHorizontalSizer);
    tagOstInfoSizer->Add(ostHorizontalSizer, 0, wxEXPAND, 5);

    AddToSizer(songLengthLabel, songLengthTextBox, timingHorizontalSizer1);
    AddToSizer(fadeLengthLabel, fadeLengthTextBox, timingHorizontalSizer1);
    AddToSizer(introLengthLabel, introLengthTextBox, timingHorizontalSizer1);
    AddToSizer(loopLengthLabel, loopLengthTextBox, timingHorizontalSizer2);
    AddToSizer(loopTimesLabel, loopTimesTextBox, timingHorizontalSizer2);
    AddToSizer(endLengthLabel, endLengthTextBox, timingHorizontalSizer2);
    tagTimingSizer->Add(timingHorizontalSizer1, 0, wxEXPAND, 5);
    tagTimingSizer->Add(timingHorizontalSizer2, 0, wxEXPAND, 5);
    
    AddToSizer(defaultDisabledChannelsLabel, defaultDisabledChannelsTextBox, 
               outputHorizontalSizer);
    AddToSizer(mutedVoicesLabel, mutedVoicesTextBox, outputHorizontalSizer);
    AddToSizer(preampLevelLabel, preampLevelTextBox, outputHorizontalSizer);
    tagAudioChannelsSizer->Add(outputHorizontalSizer, 0, wxEXPAND, 5);
    
    AddToSizer(dumperNameLabel, dumperNameTextBox, dumpInfoHorizontalSizer);
    AddToSizer(dateDumpedLabel, dateDumpedTextBox, dumpInfoHorizontalSizer);
    AddToSizer(emulatorUsedLabel, emulatorUsedTextBox, dumpInfoHorizontalSizer);
    tagDumpInfoSizer->Add(dumpInfoHorizontalSizer, 0, wxEXPAND, 5);
   
    buttonSizer->Add(propertiesButton, 0, wxALL, 5);
    buttonSizer->Add(saveButton, 0, wxALL, 5);
}

void MainWindow::CreatePanelLayout()
{

    leftColumnSizer->Add(fileListView, 1, wxALL | wxEXPAND);
    rightColumnTopSizer->Add(tagGeneralInfoSizer, 0, wxALL | wxEXPAND, 5);
    rightColumnTopSizer->Add(tagOstInfoSizer, 0, wxALL | wxEXPAND, 5);
    rightColumnTopSizer->Add(tagTimingSizer, 0, wxALL | wxEXPAND, 5);
    rightColumnTopSizer->Add(tagAudioChannelsSizer, 0, wxALL | wxEXPAND, 5);
    rightColumnTopSizer->Add(tagDumpInfoSizer, 0, wxALL | wxEXPAND, 5);
    rightColumnTopSizer->AddStretchSpacer(1);
    rightColumnBottomSizer->Add(buttonSizer, 0, wxALL | wxALIGN_RIGHT, 5);
    rightColumnSizer->Add(rightColumnTopSizer, 1, wxALL | wxEXPAND);
    rightColumnSizer->Add(rightColumnBottomSizer, 0, wxALL | wxEXPAND);

    panelSizer->Add(leftColumnSizer, 1, wxALL | wxEXPAND);
    panelSizer->Add(rightColumnSizer, 3, wxALL | wxEXPAND);
    panel->SetSizer(panelSizer);
    windowSizer->Add(panel, 1, wxEXPAND | wxALL);

    SetSizerAndFit(windowSizer);

    // Ensure the file list view column fills the entire width.
    int listViewWidth = fileListView->GetSize().GetWidth();
    fileListView->SetColumnWidth(0, listViewWidth);
}

void MainWindow::BindEvents()
{
    Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainWindow::OnOpen, this, wxID_OPEN);
    Bind(wxEVT_MENU, &MainWindow::OnSave, this, wxID_SAVE);
    Bind(wxEVT_MENU, &MainWindow::OnFileNameToTag, this, 
         WidgetID::FileNameToTag);
    Bind(wxEVT_MENU, &MainWindow::OnTagToFileName, this, 
         WidgetID::TagToFileName);
    Bind(wxEVT_MENU, &MainWindow::OnIncrementTrack, this, 
         WidgetID::IncrementTrack);
    Bind(wxEVT_MENU, &MainWindow::OnProperties, this, 
         WidgetID::Properties);
}

/*
void MainWindow::UpdateSelection()
{
    selectedFiles.clear();
    long itemIndex{ -1 };

    while ((itemIndex = fileListView->GetNextItem(itemIndex, wxLIST_NEXT_ALL, 
                                                  wxLIST_STATE_SELECTED)) != -1)
    {
        selectedFiles.push_back(files.at(itemIndex));
    }

    menuBar->Enable(wxID_SAVE, !selectedFiles.empty());
    propertiesButton->Enable(!selectedFiles.empty());
    UpdateTagSection();
    UpdateStatusBar();
}
*/

void MainWindow::UpdateTagSection()
{
    std::vector<wxString> tagTypeValues;
    std::vector<wxString> songTitleValues;
    std::vector<wxString> gameTitleValues;
    std::vector<wxString> dumperNameValues;
    std::vector<wxString> commentsValues;
    std::vector<wxString> dateDumpedValues;
    std::vector<wxString> songLengthValues;
    std::vector<wxString> fadeLengthValues;
    std::vector<wxString> songArtistValues;
    std::vector<wxString> defaultDisabledChannelsValues;
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
        Spc::Header header = file->Header();

        wxString tagType = DetermineTagType(header, tag);

        if (tagType == "-")
        {
            tagTypeValues.push_back("No Tag");
        }
        else
        {
            tagTypeValues.push_back(tagType);
        }

        songTitleValues.push_back(DetermineFieldValue(tag.SongTitle()));
        gameTitleValues.push_back(DetermineFieldValue(tag.GameTitle()));
        dumperNameValues.push_back(DetermineFieldValue(tag.DumperName()));
        commentsValues.push_back(DetermineFieldValue(tag.Comments()));
        dateDumpedValues.push_back(DetermineFieldValue(tag.DateDumped()));
        songLengthValues.push_back(DetermineFieldValue(tag.SongLength()));
        fadeLengthValues.push_back(DetermineFieldValue(tag.FadeLength()));
        songArtistValues.push_back(DetermineFieldValue(tag.SongArtist()));
        defaultDisabledChannelsValues.push_back(
            DetermineFieldValue(tag.DefaultDisabledChannels()));
        emulatorUsedValues.push_back(DetermineFieldValue(tag.EmulatorUsed()));
        ostTitleValues.push_back(DetermineFieldValue(tag.OstTitle()));
        ostDiscValues.push_back(DetermineFieldValue(tag.OstDisc()));
        ostTrackValues.push_back(DetermineFieldValue(tag.OstTrack()));
        publisherNameValues.push_back(DetermineFieldValue(tag.PublisherName()));
        copyrightYearValues.push_back(DetermineFieldValue(tag.CopyrightYear()));
        introLengthValues.push_back(DetermineFieldValue(tag.IntroLength()));
        loopLengthValues.push_back(DetermineFieldValue(tag.LoopLength()));
        endLengthValues.push_back(DetermineFieldValue(tag.EndLength()));
        mutedVoicesValues.push_back(DetermineFieldValue(tag.MutedVoices()));
        loopTimesValues.push_back(DetermineFieldValue(tag.LoopTimes()));
        preampLevelValues.push_back(DetermineFieldValue(tag.PreampLevel()));
    }

    SetTextBox(songTitleTextBox, songTitleValues);
    SetTextBox(gameTitleTextBox, gameTitleValues);
    SetTextBox(dumperNameTextBox, dumperNameValues);
    SetTextBox(commentsTextBox, commentsValues);
    SetTextBox(dateDumpedTextBox, dateDumpedValues);
    SetTextBox(songLengthTextBox, songLengthValues);
    SetTextBox(fadeLengthTextBox, fadeLengthValues);
    SetTextBox(songArtistTextBox, songArtistValues);
    SetTextBox(defaultDisabledChannelsTextBox, defaultDisabledChannelsValues);
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

            if (defaultDisabledChannelsTextBox->GetValue() != "<multiple values>")
            {
                tag.SetDefaultDisabledChannels(
                    defaultDisabledChannelsTextBox->GetValue().ToStdString());
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

void MainWindow::OnSelectionChanged(wxListEvent& event)
{
    selectedFiles.clear();
    long itemIndex{ -1 };

    while ((itemIndex = fileListView->GetNextItem(itemIndex, wxLIST_NEXT_ALL, 
                                                  wxLIST_STATE_SELECTED)) != -1)
    {
        selectedFiles.push_back(files.at(itemIndex));
    }

    menuBar->Enable(wxID_SAVE, !selectedFiles.empty());
    menuBar->Enable(WidgetID::Properties, !selectedFiles.empty());
    menuBar->Enable(WidgetID::FileNameToTag, !selectedFiles.empty());
    menuBar->Enable(WidgetID::TagToFileName, !selectedFiles.empty());
    menuBar->Enable(WidgetID::IncrementTrack, !selectedFiles.empty());
    propertiesButton->Enable(!selectedFiles.empty());
    saveButton->Enable(!selectedFiles.empty());
    UpdateTagSection();
    UpdateStatusBar();
}

void MainWindow::OnProperties(wxCommandEvent& event)
{
    PropertiesDialog dialog{ this, selectedFiles };
    dialog.ShowModal();
}