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

#if defined(__linux__)
#include <wx/filefn.h>
#include <wx/stdpaths.h>
#endif
 
MainWindow::MainWindow(wxString version) : 
    wxFrame(nullptr, wxID_ANY, version), version{ version }
{
#if defined(_WIN32)
    // On Windows, we need to set the application icon at runtime from the
    // resource file compiled into the application.
    SetIcon(wxICON(IDI_MAIN));
#elif defined(__linux__)
    // On Linux, load the icon copied next to the executable by CMake.
    wxFileName executablePath{ wxStandardPaths::Get().GetExecutablePath() };
    wxString iconPath = executablePath.GetPathWithSep() + "id666edit.png";
    wxIconBundle icons;
    
    if (wxFileExists(iconPath))
    {
        icons.AddIcon(iconPath, wxBITMAP_TYPE_ANY);
        SetIcons(icons);
    }
#endif

    panel = new wxPanel(this);
    CreateStatusBar();
    CreateMenuBar();
    CreateSizers();
    CreateLabels();
    ResizeLabels(labels);
    CreateTextBoxes();
    CreateToolTips();
    CreateButtons();
    CreateFileListView();
    CreateTagLayout();
    CreatePanelLayout();
    BindEvents();
    SetStatusText("Ready");
    UpdateEnabledControls();
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
    timingHorizontalSizer3 = new wxBoxSizer{ wxHORIZONTAL };
    outputHorizontalSizer = new wxBoxSizer{ wxHORIZONTAL };
    dumpInfoHorizontalSizer = new wxBoxSizer{ wxHORIZONTAL };
    buttonSizer = new wxBoxSizer{ wxHORIZONTAL };
    tagGeneralInfoSizer = new wxStaticBoxSizer{ wxVERTICAL, panel, "General" };
    tagOstInfoSizer = new wxStaticBoxSizer
    { 
        wxVERTICAL, panel, "Original Soundtrack" 
    };
    tagDumpInfoSizer = new wxStaticBoxSizer{ wxVERTICAL, panel, "Dump Info" };
    tagTimingSizer = new wxStaticBoxSizer{ wxVERTICAL, panel, "Timing" };
    tagAudioChannelsSizer = new wxStaticBoxSizer
    { 
        wxVERTICAL, panel, "Audio Channels" 
    };
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

    wxStaticBox* tagTimingBox = tagTimingSizer->GetStaticBox();
    CreateLabel(songLengthLabel, tagTimingBox, labels, "Song Length (sec)");
    CreateLabel(fadeLengthLabel, tagTimingBox, labels, "Fade Length (ms)");
    CreateLabel(introLengthLabel, tagTimingBox, labels, "Intro Length (ticks)");
    CreateLabel(loopLengthLabel, tagTimingBox, labels, "Loop Length (ticks)");
    CreateLabel(endLengthLabel, tagTimingBox, labels, "End Length (ticks)");
    CreateLabel(fadeLengthExtLabel, tagTimingBox, labels, 
                "Fade Length (ticks)");
    CreateLabel(loopTimesLabel, tagTimingBox, labels, "Loop Times");

    wxStaticBox* tagAudioChannelsBox = tagAudioChannelsSizer->GetStaticBox();
    CreateLabel(defaultDisabledChannelsLabel, tagAudioChannelsBox, 
                labels, "Disabled by Default");
    CreateLabel(mutedVoicesLabel, tagAudioChannelsBox, labels, "Muted");
    CreateLabel(preampLevelLabel, tagAudioChannelsBox, labels, "Preamp Level");

    wxStaticBox* tagDumpInfoBox = tagDumpInfoSizer->GetStaticBox();
    CreateLabel(dumperNameLabel, tagDumpInfoBox, labels, "Dumper Name");
    CreateLabel(dateDumpedLabel, tagDumpInfoBox, labels, "Date Dumped");
    CreateLabel(emulatorUsedLabel, tagDumpInfoBox, labels, "Emulator Used");
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
    
    wxStaticBox* tagTimingBox = tagTimingSizer->GetStaticBox();
    songLengthTextBox = new wxTextCtrl{ tagTimingBox, wxID_ANY, "" };
    fadeLengthTextBox = new wxTextCtrl{ tagTimingBox, wxID_ANY, "" };
    introLengthTextBox = new wxTextCtrl{ tagTimingBox, wxID_ANY, "" };
    loopLengthTextBox = new wxTextCtrl{ tagTimingBox, wxID_ANY, "" };
    endLengthTextBox = new wxTextCtrl{ tagTimingBox, wxID_ANY, "" };
    fadeLengthExtTextBox = new wxTextCtrl{ tagTimingBox, wxID_ANY, "" };
    loopTimesTextBox = new wxTextCtrl{ tagTimingBox, wxID_ANY, "" };
    
    wxStaticBox* tagAudioChannelsBox = tagAudioChannelsSizer->GetStaticBox();
    defaultDisabledChannelsTextBox = new wxTextCtrl
    { 
        tagAudioChannelsBox, wxID_ANY, "" 
    };
    mutedVoicesTextBox = new wxTextCtrl{ tagAudioChannelsBox, wxID_ANY, "" };
    preampLevelTextBox = new wxTextCtrl{ tagAudioChannelsBox, wxID_ANY, "" };

    wxStaticBox* tagDumpInfoBox = tagDumpInfoSizer->GetStaticBox();
    dumperNameTextBox = new wxTextCtrl{ tagDumpInfoBox, wxID_ANY, "" };
    dateDumpedTextBox = new wxTextCtrl{ tagDumpInfoBox, wxID_ANY, "" };
    emulatorUsedTextBox = new wxTextCtrl{ tagDumpInfoBox, wxID_ANY, "" };
}

void MainWindow::CreateToolTips()
{
    songTitleTextBox->SetToolTip("The title of the song");
    gameTitleTextBox->SetToolTip("The name of the game the song came from");
    songArtistTextBox->SetToolTip(
        "The artist(s) who wrote the song for the game");
    commentsTextBox->SetToolTip("Additional comments about the song");

    ostTitleTextBox->SetToolTip(
        "The title of the original soundtrack that corresponds with the game");
    ostDiscTextBox->SetToolTip(
        "The disc number the song occured on in the original soundtrack");
    ostTrackTextBox->SetToolTip(
        "The track number of the song on the original soundtrack");
    publisherNameTextBox->SetToolTip("The publisher of the game or soundtrack");
    copyrightYearTextBox->SetToolTip(
        "The year the game or soundtrack was copyrighted");

    songLengthTextBox->SetToolTip("The length of the song in seconds");
    fadeLengthTextBox->SetToolTip(
        "The amount of time the song fades out in milliseconds");
    introLengthTextBox->SetToolTip(
        "The length of the song's intro in ticks (1/64000 of a second)");
    loopLengthTextBox->SetToolTip(
        "The length of each loop of the song (1/64000 of a second)");
    endLengthTextBox->SetToolTip(
        "The length of the song's ending in ticks (1/64000 of a second)");
    fadeLengthExtTextBox->SetToolTip(
        "The length of the song's fade out in ticks (1/64000 of a second)");
    loopTimesTextBox->SetToolTip(
        "The number of times the song loops before reaching the end");

    defaultDisabledChannelsTextBox->SetToolTip(
        "Sets which audio channels are disabled on init i.e. 00010000");
    mutedVoicesTextBox->SetToolTip(
        "Sets which audio channels are muted entirely i.e. 00010000");
    preampLevelTextBox->SetToolTip(
        "Sets the preamp level for the song (32,768 - 624,288)");

    dumperNameTextBox->SetToolTip("The name of the person who dumped the song");
    dateDumpedTextBox->SetToolTip("The date the song was dumped (DD/MM/YYYY)");
    emulatorUsedTextBox->SetToolTip(
        "The name of the emulator used to dump the song");
}

void MainWindow::CreateButtons()
{
    propertiesButton = new wxButton
    { 
        panel, WidgetID::Properties, "Properties" 
    };
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

    // Keep the list view horizontally shrinkable regardless of prior
    // auto-sized column widths, preserving sizer proportions when shrinking.
    fileListView->SetMinSize(wxSize{ 0, -1 });

    fileListView->AppendColumn("Filename");
    fileListView->Bind(wxEVT_LIST_ITEM_SELECTED, 
                       &MainWindow::OnSelectionChanged, this);
    fileListView->Bind(wxEVT_LIST_ITEM_DESELECTED, 
                       &MainWindow::OnSelectionChanged, this);
}

void MainWindow::CreateTagLayout()
{
    constexpr int buttonBorderSize{ 5 };

    wxSizerFlags horizontalFlags = wxSizerFlags(noGrowthProportion).Expand();
    wxSizerFlags buttonFlags = wxSizerFlags(noGrowthProportion);
    buttonFlags.Border(wxALL, buttonBorderSize);

    AddToSizer(songTitleLabel, songTitleTextBox, tagGeneralInfoSizer);
    AddToSizer(gameTitleLabel, gameTitleTextBox, tagGeneralInfoSizer);
    AddToSizer(songArtistLabel, songArtistTextBox, tagGeneralInfoSizer);
    AddToSizer(commentsLabel, commentsTextBox, tagGeneralInfoSizer);

    AddToSizer(ostTitleLabel, ostTitleTextBox, tagOstInfoSizer);
    AddToSizer(publisherNameLabel, publisherNameTextBox, tagOstInfoSizer);
    AddToSizer(ostDiscLabel, ostDiscTextBox, ostHorizontalSizer);
    AddToSizer(ostTrackLabel, ostTrackTextBox, ostHorizontalSizer);
    AddToSizer(copyrightYearLabel, copyrightYearTextBox, ostHorizontalSizer);
    tagOstInfoSizer->Add(ostHorizontalSizer, horizontalFlags);

    AddToSizer(songLengthLabel, songLengthTextBox, timingHorizontalSizer1);
    AddToSizer(fadeLengthLabel, fadeLengthTextBox, timingHorizontalSizer1);
    AddToSizer(introLengthLabel, introLengthTextBox, timingHorizontalSizer1);
    AddToSizer(loopLengthLabel, loopLengthTextBox, timingHorizontalSizer2);
    AddToSizer(endLengthLabel, endLengthTextBox, timingHorizontalSizer2);
    AddToSizer(fadeLengthExtLabel, fadeLengthExtTextBox, 
               timingHorizontalSizer2);
    AddToSizer(loopTimesLabel, loopTimesTextBox, timingHorizontalSizer3);

    // Keep the third timing row aligned with the 3-field rows above.
    timingHorizontalSizer3->AddStretchSpacer(growthProportion);
    timingHorizontalSizer3->AddStretchSpacer(growthProportion);

    tagTimingSizer->Add(timingHorizontalSizer1, horizontalFlags);
    tagTimingSizer->Add(timingHorizontalSizer2, horizontalFlags);
    tagTimingSizer->Add(timingHorizontalSizer3, horizontalFlags);
    AddToSizer(defaultDisabledChannelsLabel, defaultDisabledChannelsTextBox, 
               outputHorizontalSizer);
    AddToSizer(mutedVoicesLabel, mutedVoicesTextBox, outputHorizontalSizer);
    AddToSizer(preampLevelLabel, preampLevelTextBox, outputHorizontalSizer);
    tagAudioChannelsSizer->Add(outputHorizontalSizer, horizontalFlags);
    
    AddToSizer(dumperNameLabel, dumperNameTextBox, dumpInfoHorizontalSizer);
    AddToSizer(dateDumpedLabel, dateDumpedTextBox, dumpInfoHorizontalSizer);
    AddToSizer(emulatorUsedLabel, emulatorUsedTextBox, dumpInfoHorizontalSizer);
    tagDumpInfoSizer->Add(dumpInfoHorizontalSizer, horizontalFlags);
   
    buttonSizer->Add(propertiesButton, buttonFlags);
    buttonSizer->Add(saveButton, buttonFlags);
}

void MainWindow::CreatePanelLayout()
{
    constexpr int staticBoxBorderSize{ 5 };

    wxSizerFlags leftColumnFlags = wxSizerFlags(growthProportion).Expand();
    wxSizerFlags rightColumnFlags = wxSizerFlags(growthProportion).Expand();
    wxSizerFlags rightColumnTopFlags = wxSizerFlags(noGrowthProportion);
    wxSizerFlags rightColumnBottomFlags = wxSizerFlags(noGrowthProportion);
    wxSizerFlags panelFlags = wxSizerFlags(growthProportion).Expand();
    wxSizerFlags windowFlags = wxSizerFlags(growthProportion).Expand();
    rightColumnTopFlags.Expand();
    rightColumnTopFlags.Border(wxALL, staticBoxBorderSize);
    rightColumnBottomFlags.Align(wxALIGN_RIGHT);
    rightColumnBottomFlags.Border(wxALL, staticBoxBorderSize);

    leftColumnSizer->Add(fileListView, leftColumnFlags);

    rightColumnTopSizer->Add(tagGeneralInfoSizer, rightColumnTopFlags);
    rightColumnTopSizer->Add(tagOstInfoSizer, rightColumnTopFlags);
    rightColumnTopSizer->Add(tagTimingSizer, rightColumnTopFlags);
    rightColumnTopSizer->Add(tagAudioChannelsSizer, rightColumnTopFlags);
    rightColumnTopSizer->Add(tagDumpInfoSizer, rightColumnTopFlags);
    rightColumnTopSizer->AddStretchSpacer(1);

    rightColumnBottomSizer->Add(buttonSizer, rightColumnBottomFlags);

    rightColumnSizer->Add(rightColumnTopSizer, rightColumnFlags);
    wxSizerFlags rightColumnFlagsMod = wxSizerFlags(rightColumnFlags);
    rightColumnFlagsMod.Proportion(noGrowthProportion);
    rightColumnSizer->Add(rightColumnBottomSizer, rightColumnFlagsMod);

    panelSizer->Add(leftColumnSizer, panelFlags);
    wxSizerFlags panelFlagsMod = wxSizerFlags(panelFlags);
    panelFlagsMod.Proportion(tripleGrowthProportion);
    panelSizer->Add(rightColumnSizer, panelFlagsMod);

    panel->SetSizer(panelSizer);

    windowSizer->Add(panel, windowFlags);

    SetSizerAndFit(windowSizer);
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
    fileListView->Bind(wxEVT_SIZE, &MainWindow::OnFileListViewResize, this);
}

void MainWindow::UpdateEnabledControls()
{
    bool hasSelectedFiles = !selectedFiles.empty();
    propertiesButton->Enable(hasSelectedFiles);
    saveButton->Enable(hasSelectedFiles);
    menuBar->Enable(wxID_SAVE, hasSelectedFiles);
    menuBar->Enable(WidgetID::FileNameToTag, hasSelectedFiles);
    menuBar->Enable(WidgetID::TagToFileName, hasSelectedFiles);
    menuBar->Enable(WidgetID::IncrementTrack, hasSelectedFiles);
    tagGeneralInfoSizer->GetStaticBox()->Enable(hasSelectedFiles);
    tagOstInfoSizer->GetStaticBox()->Enable(hasSelectedFiles);
    tagTimingSizer->GetStaticBox()->Enable(hasSelectedFiles);
    tagAudioChannelsSizer->GetStaticBox()->Enable(hasSelectedFiles);
    tagDumpInfoSizer->GetStaticBox()->Enable(hasSelectedFiles);
}

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
    std::vector<wxString> fadeLengthExtValues;
    std::vector<wxString> mutedVoicesValues;
    std::vector<wxString> loopTimesValues;
    std::vector<wxString> preampLevelValues;

    for (std::shared_ptr<Spc::File> file : selectedFiles)
    {
        Spc::Id666::Tag tag = file->Tag();
        Spc::Header header = file->Header();

        wxString tagType = GetTagType(header, tag);

        if (tagType == "-")
        {
            tagTypeValues.push_back("No Tag");
        }
        else
        {
            tagTypeValues.push_back(tagType);
        }

        songTitleValues.push_back(GetValueOrPlaceholder(tag.SongTitle()));
        gameTitleValues.push_back(GetValueOrPlaceholder(tag.GameTitle()));
        dumperNameValues.push_back(GetValueOrPlaceholder(tag.DumperName()));
        commentsValues.push_back(GetValueOrPlaceholder(tag.Comments()));
        dateDumpedValues.push_back(GetValueOrPlaceholder(tag.DateDumped()));
        songLengthValues.push_back(GetValueOrPlaceholder(tag.SongLength()));
        fadeLengthValues.push_back(GetValueOrPlaceholder(tag.FadeLength()));
        songArtistValues.push_back(GetValueOrPlaceholder(tag.SongArtist()));
        defaultDisabledChannelsValues.push_back(
            GetValueOrPlaceholder(tag.DefaultDisabledChannels()));
        emulatorUsedValues.push_back(GetValueOrPlaceholder(tag.EmulatorUsed()));
        ostTitleValues.push_back(GetValueOrPlaceholder(tag.OstTitle()));
        ostDiscValues.push_back(GetValueOrPlaceholder(tag.OstDisc()));
        ostTrackValues.push_back(GetValueOrPlaceholder(tag.OstTrack()));
        publisherNameValues.push_back(
            GetValueOrPlaceholder(tag.PublisherName()));
        copyrightYearValues.push_back(
            GetValueOrPlaceholder(tag.CopyrightYear()));
        introLengthValues.push_back(GetValueOrPlaceholder(tag.IntroLength()));
        loopLengthValues.push_back(GetValueOrPlaceholder(tag.LoopLength()));
        endLengthValues.push_back(GetValueOrPlaceholder(tag.EndLength()));
        fadeLengthExtValues.push_back(
            GetValueOrPlaceholder(tag.FadeLengthExt()));
        mutedVoicesValues.push_back(GetValueOrPlaceholder(tag.MutedVoices()));
        loopTimesValues.push_back(GetValueOrPlaceholder(tag.LoopTimes()));
        preampLevelValues.push_back(GetValueOrPlaceholder(tag.PreampLevel()));
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
    SetTextBox(fadeLengthExtTextBox, fadeLengthExtValues);
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
            wxString tagType = GetTagType(header, tag);

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
                   << GetCommonValue(versionMinorValues) 
                   << " | Contains Tag: " 
                   << GetCommonValue(headerContainsTagValues)
                   << " | Tag Type: " << GetCommonValue(tagTypeValues);
        SetStatusText(statusText);
    }
}

void MainWindow::SetTextBox(wxTextCtrl* textBox, 
                            const std::vector<wxString>& values)
{
    if (values.empty())
    {
        textBox->Clear();
    }
    else
    {
        wxString value = GetCommonValue(values);

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

void MainWindow::RefreshFileListView()
{
    fileListView->DeleteAllItems();

    for (size_t itemIndex = 0; itemIndex < files.size(); itemIndex++)
    {
        wxFileName fileName{ files.at(itemIndex)->Path() };
        fileListView->InsertItem(static_cast<long>(itemIndex),
                                 fileName.GetFullName());
    }
}

void MainWindow::TrySetTagField(
    Spc::Id666::Tag& tag,
    wxTextCtrl* textBox,
    const wxString& fieldName,
    const wxString& filePath,
    const std::function<void(Spc::Id666::Tag&, const std::string&)>& setField)
{
    if (textBox->GetValue() == "<multiple values>")
    {
        return;
    }

    try
    {
        setField(tag, textBox->GetValue().ToStdString());
    }
    catch (const std::exception& ex)
    {
        wxString message;
        message << fieldName << "\n\nError: unable to set field value."
                << "\nReason: " << ex.what()
                << "\n\nFile: " << filePath;
        wxMessageBox(message, "Error Saving File", wxOK | wxICON_ERROR, this);
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
    {
        return;
    }

    files.clear();
    wxArrayString filePaths;
    dialog.GetPaths(filePaths);

    for (const wxString& path : filePaths)
    {
        auto file = std::make_shared<Spc::File>(path.ToStdString());
        file->Load();
        files.push_back(file);
    }

    RefreshFileListView();

    if (!files.empty())
    {
        // Preselect the first file so tag fields are ready for editing.
        fileListView->Select(0);
        fileListView->Focus(0);
        fileListView->EnsureVisible(0);

        selectedFiles.clear();
        selectedFiles.push_back(files.front());
        UpdateEnabledControls();
        UpdateTagSection();
        UpdateStatusBar();
    }
}

void MainWindow::OnSave(wxCommandEvent& event)
{
    for (std::shared_ptr<Spc::File> file : selectedFiles)
    {
        Spc::Id666::Tag tag = file->Tag();
        wxString filePath = file->Path();

        TrySetTagField(tag, songTitleTextBox, "Song Title", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetSongTitle(value);
            });
        TrySetTagField(tag, gameTitleTextBox, "Game Title", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetGameTitle(value);
            });
        TrySetTagField(tag, dumperNameTextBox, "Dumper Name", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetDumperName(value);
            });
        TrySetTagField(tag, commentsTextBox, "Comments", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetComments(value);
            });
        TrySetTagField(tag, dateDumpedTextBox, "Date Dumped", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetDateDumped(value);
            });
        TrySetTagField(tag, songLengthTextBox, "Song Length", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetSongLength(value);
            });
        TrySetTagField(tag, fadeLengthTextBox, "Fade Length", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetFadeLength(value);
            });
        TrySetTagField(tag, songArtistTextBox, "Song Artist", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetSongArtist(value);
            });
        TrySetTagField(tag, defaultDisabledChannelsTextBox,
            "Disabled by Default", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetDefaultDisabledChannels(value);
            });
        TrySetTagField(tag, emulatorUsedTextBox, "Emulator Used", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetEmulatorUsed(value);
            });
        TrySetTagField(tag, ostTitleTextBox, "OST Title", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetOstTitle(value);
            });
        TrySetTagField(tag, ostDiscTextBox, "OST Disc", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetOstDisc(value);
            });
        TrySetTagField(tag, ostTrackTextBox, "OST Track", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetOstTrack(value);
            });
        TrySetTagField(tag, publisherNameTextBox, "Publisher Name", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetPublisherName(value);
            });
        TrySetTagField(tag, copyrightYearTextBox, "Copyright Year", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetCopyrightYear(value);
            });
        TrySetTagField(tag, introLengthTextBox, "Intro Length", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetIntroLength(value);
            });
        TrySetTagField(tag, loopLengthTextBox, "Loop Length", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetLoopLength(value);
            });
        TrySetTagField(tag, endLengthTextBox, "End Length", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetEndLength(value);
            });
        TrySetTagField(tag, fadeLengthExtTextBox, 
                      "Fade Length (ticks)", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetFadeLengthExt(value);
            });
        TrySetTagField(tag, mutedVoicesTextBox, "Muted Voices", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetMutedVoices(value);
            });
        TrySetTagField(tag, loopTimesTextBox, "Loop Times", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetLoopTimes(value);
            });
        TrySetTagField(tag, preampLevelTextBox, "Preamp Level", filePath,
            [](Spc::Id666::Tag& targetTag, const std::string& value)
            {
                targetTag.SetPreampLevel(value);
            });

        file->SetTag(tag);

        try
        {
            file->Save();
        }
        catch (const std::exception& ex)
        {
            wxString message;
            message << "Failed to save file:\n" << filePath
                    << "\n\nReason: " << ex.what();
            wxMessageBox(message, "Error Saving File", 
                         wxOK | wxICON_ERROR, this);
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
        RefreshFileListView();
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

    UpdateEnabledControls();
    UpdateTagSection();
    UpdateStatusBar();
}

void MainWindow::OnProperties(wxCommandEvent& event)
{
    PropertiesDialog dialog{ this, selectedFiles };
    dialog.ShowModal();
}

void MainWindow::OnFileListViewResize(wxSizeEvent& event)
{
    // Use the new size from the event to avoid stale dimensions while resizing.
    int columnWidth = event.GetSize().GetWidth();
    columnWidth = columnWidth > 0 ? columnWidth : 0;
    fileListView->SetColumnWidth(0, columnWidth);

    // Call Skip() to allow the control to process the event properly.
    event.Skip();
}