#include <wx/wx.h>
#include "MainFrame.h"

class MyApp : public wxApp
{
    Data data;

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