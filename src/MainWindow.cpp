#include "MainWindow.h"
 
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "ID666Edit")
{
    panel = new wxPanel(this);
    CreateStatusBar();
    CreateMenuBar();
    CreateSizers();
    CreateLabelText();
    CreateValueText();
    CreateTextBoxes();
    CreateFileListView();
    CreateHeaderLayout();
    CreateTagLayout();
    CreatePanelLayout();
    BindEvents();
    SetStatusText("Ready");
}

void MainWindow::CreateMenuBar()
{
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(wxID_EXIT);
    fileMenu->Append(WidgetID::Open, "&Open...\tCtrlO",
        "Open .spc files");
    fileMenu->Append(WidgetID::Save, "&Save...\tCtrlO",
        "Saves changes to the .spc files");

    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");

    SetMenuBar(menuBar);
}

void MainWindow::CreateSizers()
{
    leftColumnSizer = new wxBoxSizer{ wxVERTICAL };
    rightColumnSizer = new wxBoxSizer{ wxVERTICAL };
    headerColumn1Sizer = new wxBoxSizer{ wxVERTICAL };
    headerColumn2Sizer = new wxBoxSizer{ wxVERTICAL };
    tagColumn1Sizer = new wxBoxSizer{ wxVERTICAL };
    tagColumn2Sizer = new wxBoxSizer{ wxVERTICAL };
    headerSizer = new wxStaticBoxSizer{  wxHORIZONTAL, panel, "Header" };
    tagSizer = new wxStaticBoxSizer{ wxHORIZONTAL, panel, "Tag" };
    panelSizer = new wxBoxSizer{ wxHORIZONTAL };
    windowSizer = new wxBoxSizer{ wxVERTICAL };
}

void MainWindow::CreateLabelText()
{
    idLabel = new wxStaticText{ panel, wxID_ANY, "ID:" };
    containsTagLabel = new wxStaticText{ panel, wxID_ANY, "Contains Tag:" };
    tagTypeLabel = new wxStaticText{ panel, wxID_ANY, "Tag Type:" };
    versionMinorLabel = new wxStaticText{ panel, wxID_ANY, "Version Minor:" };
    pcRegisterLabel = new wxStaticText{ panel, wxID_ANY, "PC Register:" };
    aRegisterLabel = new wxStaticText{ panel, wxID_ANY, "A Register:" };
    xRegisterLabel = new wxStaticText{ panel, wxID_ANY, "X Register:" };
    yRegisterLabel = new wxStaticText{ panel, wxID_ANY, "Y Register:" };
    pswRegisterLabel = new wxStaticText{ panel, wxID_ANY, "PSW Register:" };
    spRegisterLabel = new wxStaticText{ panel, wxID_ANY, "SP Register:" };
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
    id = new wxStaticText{ panel, wxID_ANY, "-" };
    containsTag = new wxStaticText{ panel, wxID_ANY, "-" };
    tagType = new wxStaticText{ panel, wxID_ANY, "-" };
    versionMinor = new wxStaticText{ panel, wxID_ANY, "-" };
    pcRegister = new wxStaticText{ panel, wxID_ANY, "-" };
    aRegister = new wxStaticText{ panel, wxID_ANY, "-" };
    xRegister = new wxStaticText{ panel, wxID_ANY, "-" };
    yRegister = new wxStaticText{ panel, wxID_ANY, "-" };
    pswRegister = new wxStaticText{ panel, wxID_ANY, "-" };
    spRegister = new wxStaticText{ panel, wxID_ANY, "-" };
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
    fileListView = new wxListView{ panel, wxID_ANY, wxDefaultPosition };
    fileListView->AppendColumn("Filename");
    fileListView->Bind(wxEVT_LIST_ITEM_SELECTED, &MainWindow::OnSelected, this);
}

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
}

void MainWindow::CreateTagLayout()
{
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
    rightColumnSizer->Add(headerSizer, 0, wxALL | wxEXPAND, 5);
    rightColumnSizer->Add(tagSizer, 0, wxALL | wxEXPAND, 5);
    panelSizer->Add(leftColumnSizer, 1, wxALL | wxEXPAND);
    panelSizer->Add(rightColumnSizer, 2, wxALL | wxEXPAND);
    panel->SetSizer(panelSizer);
    windowSizer->Add(panel, 1, wxEXPAND | wxALL);

    // Because the status bar isn't included in layout calculations, we need
    // to add the status bar height to the spacer to avoid veritcal cutoff.
    int statusBarHeight = GetStatusBar()->GetSize().GetHeight();
    rightColumnSizer->AddSpacer(statusBarHeight);

    SetSizerAndFit(windowSizer);
}

void MainWindow::BindEvents()
{
    Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainWindow::OnOpen, this, WidgetID::Open);
    Bind(wxEVT_MENU, &MainWindow::OnSave, this, WidgetID::Save);
}

void MainWindow::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MainWindow::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("v0.9.0", "About ID666Edit", wxOK | wxICON_INFORMATION);
}

void MainWindow::OnOpen(wxCommandEvent& event)
{
    wxFileDialog dialog(this);

    if(dialog.ShowModal() != wxID_OK) 
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
        fileListView->InsertItem(itemIndex, path);
        itemIndex++;
    }
}

void MainWindow::OnSave(wxCommandEvent& event)
{

}

void MainWindow::OnSelected(wxListEvent& event)
{
    long selectedIndex = event.GetIndex();
    std::shared_ptr<Spc::File> file = files.at(selectedIndex);
    Spc::Header header = file->Header();
    id->SetLabelText(wxString{ header.ID.ToString() });

    if (file->HeaderContainsTag())
    {
        containsTag->SetLabelText("True");

        switch (file->TagType())
        {
            case Spc::TagType::Text:
                tagType->SetLabelText("Text");
                break;
            case Spc::TagType::Binary:
                tagType->SetLabelText("Binary");
                break;
            case Spc::TagType::TextMixed:
                tagType->SetLabelText("Mixed");
                break;
            default:
                tagType->SetLabelText("-");
        }
    }
    else
    {
        containsTag->SetLabelText("False");
    }

    versionMinor->SetLabelText(wxString{ header.versionMinor.ToString() });
    pcRegister->SetLabelText(wxString{ header.pcRegister.ToString() });
    aRegister->SetLabelText(wxString{ header.aRegister.ToString() });
    xRegister->SetLabelText(wxString{ header.xRegister.ToString() });
    yRegister->SetLabelText(wxString{ header.yRegister.ToString() });
    pswRegister->SetLabelText(wxString{ header.pswRegister.ToString() });
    spRegister->SetLabelText(wxString{ header.spRegister.ToString() });
    
    songTitleTextBox->SetValue(wxString{ file->SongTitle().ToString() });
    gameTitleTextBox->SetValue(wxString{ file->GameTitle().ToString() });
    dumperNameTextBox->SetValue(wxString{ file->DumperName().ToString() });
    commentsTextBox->SetValue(wxString{ file->Comments().ToString() });
    dateDumpedTextBox->SetValue(wxString{ file->DateDumped().ToString() });
    songLengthTextBox->SetValue(wxString{ file->SongLength().ToString() });
    fadeLengthTextBox->SetValue(wxString{ file->FadeLength().ToString() });
    songArtistTextBox->SetValue(wxString{ file->SongArtist().ToString() });
    defaultChannelStateTextBox->SetValue(wxString
    { 
        file->DefaultChannelState().ToString() 
    });
    emulatorUsedTextBox->SetValue(wxString{ file->EmulatorUsed().ToString() });
    ostTitleTextBox->SetValue(wxString{ file->OstTitle().ToString() });
    ostDiscTextBox->SetValue(wxString{ file->OstDisc().ToString() });
    ostTrackTextBox->SetValue(wxString{ file->OstTrack().ToString() });
    publisherNameTextBox->SetValue(wxString{file->PublisherName().ToString()});
    copyrightYearTextBox->SetValue(wxString{file->CopyrightYear().ToString()});
    introLengthTextBox->SetValue(wxString{ file->IntroLength().ToString()});
    loopLengthTextBox->SetValue(wxString{ file->LoopLength().ToString() });
    endLengthTextBox->SetValue(wxString{ file->EndLength().ToString() });
    mutedVoicesTextBox->SetValue(wxString{ file->MutedVoices().ToString() });
    loopTimesTextBox->SetValue(wxString{ file->LoopTimes().ToString() });
    preampLevelTextBox->SetValue(wxString{ file->LoopTimes().ToString() });
}

void AddToSizer(wxStaticText* label, wxStaticText* value, wxBoxSizer* sizer)
{
    // Set consistent label and value widths to ensure visual alignment.
    label->SetMinSize(wxSize{ 150, -1 });
    value->SetMinSize(wxSize{ 225, -1 });

    wxBoxSizer* valueSizer = new wxBoxSizer{ wxHORIZONTAL };
    valueSizer->Add(label, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    valueSizer->Add(value, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    sizer->Add(valueSizer, 0, wxALL | wxEXPAND);
}

void AddToSizer(wxStaticText* label, wxTextCtrl* textBox, wxBoxSizer* sizer)
{
    // Set a consistent label width when adding to the sizer to ensure the
    // corresponding text boxes are all aligned. 
    label->SetMinSize(wxSize{ 150, -1 });
    textBox->SetMinSize(wxSize{ 225, -1 });

    wxBoxSizer* textBoxSizer = new wxBoxSizer{ wxHORIZONTAL };
    textBoxSizer->Add(label, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    textBoxSizer->Add(textBox, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    sizer->Add(textBoxSizer, 0, wxALL | wxEXPAND);
}