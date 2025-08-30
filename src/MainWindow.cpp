#include "MainWindow.h"
 
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "ID666Edit")
{
    panel = new wxPanel(this);
    CreateMenuBar();
    CreateSizers();
    CreateLabelText();
    CreateValueText();
    CreateTextBoxes();
    CreateFileListView();
    CreateHeaderLayout();
    CreateTagLayout();
    CreatePanelLayout();
    CreateStatusBar();
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
    headerLabelColumn1Sizer = new wxBoxSizer{ wxVERTICAL };
    headerValueColumn1Sizer = new wxBoxSizer{ wxVERTICAL };
    headerLabelColumn2Sizer = new wxBoxSizer{ wxVERTICAL };
    headerValueColumn2Sizer = new wxBoxSizer{ wxVERTICAL };
    tagLabelColumnSizer = new wxBoxSizer{ wxVERTICAL };
    tagTextBoxColumnSizer = new wxBoxSizer{ wxVERTICAL };
    headerSizer = new wxStaticBoxSizer{  wxHORIZONTAL, panel, "Header" };
    tagSizer = new wxStaticBoxSizer{ wxHORIZONTAL, panel, "Tag" };
    panelSizer = new wxBoxSizer{ wxHORIZONTAL };
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
}

void MainWindow::CreateFileListView()
{
    fileListView = new wxListView{ panel, wxID_ANY, wxDefaultPosition };
    fileListView->AppendColumn("Filename");
    fileListView->Bind(wxEVT_LIST_ITEM_SELECTED, &MainWindow::OnSelected, this);
}

void MainWindow::CreateHeaderLayout()
{
    headerLabelColumn1Sizer->Add(idLabel, 0, wxALL, 5);
    headerLabelColumn1Sizer->Add(containsTagLabel, 0, wxALL, 5);
    headerLabelColumn1Sizer->Add(tagTypeLabel, 0, wxALL, 5);
    headerLabelColumn1Sizer->Add(versionMinorLabel, 0, wxALL, 5);

    headerValueColumn1Sizer->Add(id, 0, wxALL, 5);
    headerValueColumn1Sizer->Add(containsTag, 0, wxALL, 5);
    headerValueColumn1Sizer->Add(tagType, 0, wxALL, 5);
    headerValueColumn1Sizer->Add(versionMinor, 0, wxALL, 5);
    
    headerLabelColumn2Sizer->Add(pcRegisterLabel, 0, wxALL, 5);
    headerLabelColumn2Sizer->Add(aRegisterLabel, 0, wxALL, 5);
    headerLabelColumn2Sizer->Add(xRegisterLabel, 0, wxALL, 5);
    headerLabelColumn2Sizer->Add(yRegisterLabel, 0, wxALL, 5);
    headerLabelColumn2Sizer->Add(pswRegisterLabel, 0, wxALL, 5);
    headerLabelColumn2Sizer->Add(spRegisterLabel, 0, wxALL, 5);

    headerValueColumn2Sizer->Add(pcRegister, 0, wxALL, 5);
    headerValueColumn2Sizer->Add(aRegister, 0, wxALL, 5);
    headerValueColumn2Sizer->Add(xRegister, 0, wxALL, 5);
    headerValueColumn2Sizer->Add(yRegister, 0, wxALL, 5);
    headerValueColumn2Sizer->Add(pswRegister, 0, wxALL, 5);
    headerValueColumn2Sizer->Add(spRegister, 0, wxALL, 5);

    headerSizer->Add(headerLabelColumn1Sizer, 0, wxALL | wxEXPAND);
    headerSizer->Add(headerValueColumn1Sizer, 0, wxALL | wxEXPAND);
    headerSizer->Add(headerLabelColumn2Sizer, 0, wxALL | wxEXPAND);
    headerSizer->Add(headerValueColumn2Sizer, 0, wxALL | wxEXPAND);
}

void MainWindow::CreateTagLayout()
{
    tagLabelColumnSizer->Add(songTitleLabel, 0, wxALL, 5);
    tagLabelColumnSizer->Add(gameTitleLabel, 0, wxALL, 5);

    tagTextBoxColumnSizer->Add(songTitleTextBox, 0, wxALL, 5);
    tagTextBoxColumnSizer->Add(gameTitleTextBox, 0, wxALL, 5);

    tagSizer->Add(tagLabelColumnSizer, 0, wxALL | wxEXPAND);
    tagSizer->Add(tagTextBoxColumnSizer, 0, wxALL | wxEXPAND);
}

void MainWindow::CreatePanelLayout()
{
    leftColumnSizer->Add(fileListView, 1, wxALL | wxEXPAND);
    rightColumnSizer->Add(headerSizer, 0, wxALL | wxEXPAND, 5);
    rightColumnSizer->Add(tagSizer, 0, wxALL | wxEXPAND, 5);
    panelSizer->Add(leftColumnSizer, 1, wxALL | wxEXPAND);
    panelSizer->Add(rightColumnSizer, 1, wxALL | wxEXPAND, 5);
    panel->SetSizer(panelSizer);
    Fit();
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
}