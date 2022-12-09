#include "main.h"
#include "mainwindow.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  MainWindow *mainWindow = new MainWindow(wxT("Masada - Antivirus"), 640, 480);
  mainWindow->Show(true);

  return true;
}