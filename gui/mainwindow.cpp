#include "mainwindow.h"
#include "../FileVault.h"
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
  m_item_list = new wxListCtrl(m_Panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
  m_Button = new wxButton(m_Panel, wxID_ANY, wxT("Quick Scan"),
                          wxPoint(5, 35), wxSize(80, 25));
  m_Button_2 = new wxButton(m_Panel, wxID_ANY, wxT("Full Scan"),
                            wxPoint(5, 35), wxSize(80, 25));
  m_Button_3 = new wxButton(m_Panel, wxID_ANY, wxT("Unquarantine"),
                            wxPoint(5, 35), wxSize(80, 25));
  m_Button_4 = new wxButton(m_Panel, wxID_ANY, wxT("Delete"),
                            wxPoint(5, 35), wxSize(80, 25));

    m_EditBox = new wxTextCtrl(m_Panel, wxID_ANY, wxT(""),
                             wxPoint(5, 35), wxSize(160, 24));

  // Add first column
  wxListItem col0;
  col0.SetId(0);
  col0.SetText(_("File Path"));
  col0.SetWidth(100);
  m_item_list->InsertColumn(0, col0);

  FileVault quarantine("quarantine.vault");
  std::vector<std::string> items = quarantine.list();

  for (int n = 0; n < (int) items.size(); n++)
  {
    wxListItem item;
    item.SetId(n);
    item.SetText(items[n]);

    m_item_list->InsertItem(item);

    m_item_list->SetItem(n, 0, items[n]);
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


