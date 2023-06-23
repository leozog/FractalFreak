#include <wx/wx.h>

#include "MainFrame.h"
#include "AppData.h"

class MyApp : public wxApp
{
    AppData data;

public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MainFrame *frame = new MainFrame(nullptr, data);
    frame->Show(true);
    return true;
}