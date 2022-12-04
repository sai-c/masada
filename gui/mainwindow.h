#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/filepicker.h>


class MainWindow : public wxFrame
{
public:
  MainWindow(const wxString& title, int width, int height);
private:
  wxPanel * m_Panel;  
  wxTextCtrl * m_EditBox;
  wxButton * m_Button;
  wxButton * m_Button_2;
  void OnButtonClick(wxCommandEvent & event);
  void OnPathChanged(wxFileDirPickerEvent& evt);
  wxDECLARE_EVENT_TABLE();

};

#endif