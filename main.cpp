#include <wx/wx.h>
#include "ui/include/projekt.h"
#include "ui/include/Frame.h"

class MyApp : public wxApp {

public:

 virtual bool OnInit();
 virtual int OnExit() { return 0; }

};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit() 
{
 SetProcessDPIAware();
 Frame *mainFrame = new Frame(NULL);

 mainFrame->Show(true);
 
 SetTopWindow(mainFrame);

 return true;
}