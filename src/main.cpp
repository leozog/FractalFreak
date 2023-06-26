#include <wx/wx.h>

#include "ui/MainFrame.h"
#include "AppData.h"

class MyApp : public wxApp
{
    AppData data; // object in which entire application data is stored including Animation, AnimationPath etc.

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