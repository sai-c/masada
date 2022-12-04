#include "mainwindow.h"
#include <iostream>


MainWindow::MainWindow(const wxString& title, int width, int height)
  : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(width, height))
{
  m_Panel = new wxPanel(this, wxID_ANY);
  wxDirPickerCtrl* dirPickerCtrl = new wxDirPickerCtrl(m_Panel, 32700,
        wxEmptyString, wxDirSelectorPromptStr,
        wxDefaultPosition, wxSize(350, wxDefaultCoord));
  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

  m_EditBox = new wxTextCtrl(m_Panel, wxID_ANY, wxT(""), 
                             wxPoint(5,35), wxSize(160, 24));

  m_Button = new wxButton(m_Panel, wxID_ANY, wxT("Quick Scan"), 
                          wxPoint(5,35), wxSize(80, 25)); 
  m_Button_2 = new wxButton(m_Panel, wxID_ANY, wxT("Full Scan"), 
                          wxPoint(5,35), wxSize(80, 25)); 
  hbox->Add(m_Button);
  hbox->Add(m_Button_2);
  vbox->Add(dirPickerCtrl);
  vbox->Add(hbox);
  vbox->Add(m_EditBox);
  m_Button->Bind(wxEVT_BUTTON, &MainWindow::OnButtonClick, this);  
  m_Panel->SetSizer(vbox);
  Centre();
}

void MainWindow::OnButtonClick(wxCommandEvent & event)
{
  m_EditBox->SetValue(wxT("Hello World!"));
}

void MainWindow::OnPathChanged(wxFileDirPickerEvent& evt)
{
  m_EditBox->SetValue(wxT("Hello World!"));
}

// Add the event handler to the event table. As you can see we use the
// window ID to link the event handler to the wxDirPickerCtrl we created.
wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_DIRPICKER_CHANGED(32700, MainWindow::OnPathChanged)
wxEND_EVENT_TABLE()
