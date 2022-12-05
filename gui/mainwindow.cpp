#include "mainwindow.h"
#include <iostream>
#include <string>

MainWindow::MainWindow(const wxString &title, int width, int height)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(width, height))
{
  m_Panel = new wxPanel(this, wxID_ANY);
      dirPickerCtrl = new wxDirPickerCtrl(m_Panel, 32700,
                                                       wxEmptyString, wxDirSelectorPromptStr,
                                                       wxDefaultPosition, wxSize(350, wxDefaultCoord));


  wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *sideSizer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *sideSizer2 = new wxBoxSizer(wxHORIZONTAL);
  m_item_list = new wxListBox(m_Panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
  m_Button = new wxButton(m_Panel, 101, wxT("Quick Scan"),
                          wxPoint(5, 35), wxSize(80, 25));
  m_Button_2 = new wxButton(m_Panel, 102, wxT("Full Scan"),
                            wxPoint(5, 35), wxSize(80, 25));
  m_Button_3 = new wxButton(m_Panel, 103, wxT("Unquarantine"),
                            wxPoint(5, 35), wxSize(80, 25));
  m_Button_4 = new wxButton(m_Panel, 104, wxT("Delete"),
                            wxPoint(5, 35), wxSize(80, 25));

    m_EditBox = new wxTextCtrl(m_Panel, wxID_ANY, wxT(""),
                             wxPoint(5, 35), wxSize(160, 24));
  // Add first column
  quarantine = new FileVault("quarantine.vault");
  quarantine->add("test.txt");

  std::vector<std::string> items = quarantine->list();

  for (int n = 0; n < (int) items.size(); n++)
  {
    m_item_list->Append(items[n]);

  }

  topSizer->Add(dirPickerCtrl, 0, wxALIGN_CENTER);
    sideSizer2->Add(m_Button);
  sideSizer2->Add(m_Button_2);

  topSizer->Add(sideSizer2, 0, wxALIGN_CENTER);

  topSizer->Add(m_item_list, 0, wxALIGN_CENTER);

  sideSizer->Add(m_Button_3);
  sideSizer->Add(m_Button_4);
  topSizer->Add(sideSizer, 0, wxALIGN_CENTER);
  topSizer->Add(m_EditBox, 0, wxALIGN_CENTER);
  m_Panel->SetSizer(topSizer);
}

void MainWindow::OnQuickButtonClicked(wxCommandEvent& evt)
{
  wxString dir = dirPickerCtrl->GetPath();
  
  m_EditBox->SetValue(dir);
  evt.Skip();
}
void MainWindow::OnFullButtonClicked(wxCommandEvent& evt)
{
  wxString dir = dirPickerCtrl->GetPath();
  
  m_EditBox->SetValue(dir);

  evt.Skip();
}
void MainWindow::OnUnqButtonClicked(wxCommandEvent& evt)
{
  int id = m_item_list->GetSelection();
  if (id >= 0) {
    wxString test = m_item_list->GetString(id);
    quarantine->extract(test.ToStdString());
  }
  evt.Skip();
}
void MainWindow::OnDelButtonClicked(wxCommandEvent& evt)
{
  evt.Skip();
}


wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_BUTTON(101, MainWindow::OnQuickButtonClicked)
    EVT_BUTTON(102, MainWindow::OnFullButtonClicked)
    EVT_BUTTON(103, MainWindow::OnUnqButtonClicked)
    EVT_BUTTON(104, MainWindow::OnDelButtonClicked)
wxEND_EVENT_TABLE()
