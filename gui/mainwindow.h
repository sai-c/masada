#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/wx.h>
#include <wx/sizer.h>
#include <memory>

#include <FileVault.h>
#include "Controller.h"

#include <wx/filepicker.h>
#include <wx/listctrl.h>

class MainWindow : public wxFrame
{
public:
  MainWindow(const wxString &title, int width, int height);
  void OnQuickButtonClicked(wxCommandEvent &evt);
  void OnFullButtonClicked(wxCommandEvent &evt);
  void OnUnqButtonClicked(wxCommandEvent &evt);
  void OnDelButtonClicked(wxCommandEvent &evt);
  void updateQuarantine();

private:
  std::unique_ptr<Controller> controller;
  std::shared_ptr<Controller> makeController();
  wxPanel *m_Panel;
  wxPanel *m_Panel_2;
  wxPanel *m_Panel_3;
  wxPanel *m_Panel_4;
  wxTextCtrl *m_EditBox;
  wxButton *m_Button;
  wxButton *m_Button_2;
  wxButton *m_Button_3;
  wxButton *m_Button_4;
  wxListBox *m_item_list;
  wxListCtrl *m_item_list2;
  wxDirPickerCtrl *dirPickerCtrl;
  wxDECLARE_EVENT_TABLE();
};

#endif
