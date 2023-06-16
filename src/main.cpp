#include <wx/wx.h>
#include "MainFrame.h"

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MainFrame *frame = new MainFrame(nullptr);
    frame->Show(true);
    return true;
}