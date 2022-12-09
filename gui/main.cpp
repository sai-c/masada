#include "main.h"
#include "mainwindow.h"
#include "Controller.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  MainWindow *mainWindow = new MainWindow(wxT("Masada - Antivirus"), 640, 480);
  mainWindow->Show(true);
  auto c = std::make_shared<Controller>("hashes.txt", "sigs.txt");
  std::thread realTimeScanning(&Controller::launchRealTimeScan, c);
  realTimeScanning.detach();
  return true;
}