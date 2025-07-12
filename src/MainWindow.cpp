#include "MainWindow.h"
 
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "ID666Edit")
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

    CreateStatusBar();
    SetStatusText("Ready");

    wxBoxSizer* leftColumnSizer = new wxBoxSizer{ wxVERTICAL };
    wxBoxSizer* rightColumnSizer = new wxBoxSizer{ wxVERTICAL };

    wxPanel* panel = new wxPanel(this);

    fileListView = new wxListView{ panel, wxID_ANY, wxDefaultPosition };
    fileListView->AppendColumn("Filename");
    fileListView->Bind(wxEVT_LIST_ITEM_SELECTED, &MainWindow::OnSelected, this);
    leftColumnSizer->Add(fileListView, 1, wxALL | wxEXPAND);

    idLabel = new wxStaticText{ panel, wxID_ANY, "ID:" };
    id = new wxStaticText{ panel, wxID_ANY, "-" };
    containsTagLabel = new wxStaticText{ panel, wxID_ANY, "Contains Tag:" };
    containsTag = new wxStaticText{ panel, wxID_ANY, "-" };
    tagTypeLabel = new wxStaticText{ panel, wxID_ANY, "Tag Type:" };
    tagType = new wxStaticText{ panel, wxID_ANY, "-" };

    wxBoxSizer* headerLabelColumnSizer = new wxBoxSizer{ wxVERTICAL };
    headerLabelColumnSizer->Add(idLabel, 0, wxALL, 5);
    headerLabelColumnSizer->Add(containsTagLabel, 0, wxALL, 5);
    headerLabelColumnSizer->Add(tagTypeLabel, 0, wxALL, 5);

    wxBoxSizer* headerValueColumnSizer = new wxBoxSizer{ wxVERTICAL };
    headerValueColumnSizer->Add(id, 0, wxALL, 5);
    headerValueColumnSizer->Add(containsTag, 0, wxALL, 5);
    headerValueColumnSizer->Add(tagType, 0, wxALL, 5);

    wxStaticBoxSizer* headerSizer = new wxStaticBoxSizer
    { 
        wxHORIZONTAL, panel, "Header" 
    };

    headerSizer->Add(headerLabelColumnSizer, 0, wxALL | wxEXPAND);
    headerSizer->Add(headerValueColumnSizer, 0, wxALL | wxEXPAND);
    rightColumnSizer->Add(headerSizer, 0, wxALL | wxEXPAND, 5);

    wxBoxSizer* panelSizer = new wxBoxSizer{ wxHORIZONTAL };
    panelSizer->Add(leftColumnSizer, 1, wxALL | wxEXPAND);
    panelSizer->Add(rightColumnSizer, 1, wxALL | wxEXPAND, 5);

    panel->SetSizer(panelSizer);

    Fit();

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
}