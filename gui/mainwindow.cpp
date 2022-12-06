#include "mainwindow.h"
#include <iostream>
#include <string>
#include "Definitions.h"
#include "IDetectionEngine.h"
#include "HashingDetectionEngine.h"
#include "PatternMatchingDetectionEngine.h"
#include "Scanner.h"
#include "Logger.h"
#include "FileVault.h"

#include <thread>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <stdio.h>
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

  updateQuarantine();

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
  m_EditBox->SetValue("Scanning " + dir);
  m_EditBox->Refresh();
  m_EditBox->Update();

  Definitions hashDefinitions("test.txt");
  Logger logger("log.txt");
  std::unique_ptr<IDetectionEngine> fullDetectionEngine = std::make_unique<PatternMatchingDetectionEngine>(hashDefinitions);
  std::unique_ptr<FileVault> quarantine = std::make_unique<FileVault>("quarantine.vault");

  std::shared_ptr<VirusHandler> virusHandler = std::make_shared<VirusHandler>(std::move(quarantine));
  Scanner fullScanner(std::move(fullDetectionEngine), virusHandler);
  fullScanner.scan(dir.ToStdString());
  m_EditBox->SetValue("Scan doen");
  updateQuarantine();
  evt.Skip();
}
void MainWindow::OnUnqButtonClicked(wxCommandEvent& evt)
{
  int id = m_item_list->GetSelection();
  wxString test = m_item_list->GetString(id);
  FileVault quarantine("quarantine.vault");

  if (id >= 0) {
    quarantine.extract(test.ToStdString());
    quarantine.remove(test.ToStdString());
  }
  quarantine.write();
  m_EditBox->SetValue("Unquarantined " + test);
  updateQuarantine();
  evt.Skip();
}
void MainWindow::OnDelButtonClicked(wxCommandEvent& evt)
{
  int id = m_item_list->GetSelection();
  wxString test = m_item_list->GetString(id);
  FileVault quarantine("quarantine.vault");
  if (id >= 0) {
    quarantine.remove(test.ToStdString());
  }
  m_EditBox->SetValue("Deleted " + test);
  quarantine.write();
  updateQuarantine();
  evt.Skip();
}
void MainWindow::updateQuarantine() {
  m_item_list->Clear();
  FileVault quarantine("quarantine.vault");

  std::vector<std::string> items = quarantine.list();

  for (int n = 0; n < (int) items.size(); n++)
  {
    m_item_list->Append(items[n]);
  }
}


wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_BUTTON(101, MainWindow::OnQuickButtonClicked)
    EVT_BUTTON(102, MainWindow::OnFullButtonClicked)
    EVT_BUTTON(103, MainWindow::OnUnqButtonClicked)
    EVT_BUTTON(104, MainWindow::OnDelButtonClicked)
wxEND_EVENT_TABLE()
