#include <wx/wx.h>
#include <memory>

#include "ui/MainWindow.h"
#include "AppData.h"

class MyApp : public wxApp
{
    std::unique_ptr<MainWindow> window;
    AppData data; // object in which entire application data is stored including Animation, AnimationPath etc.

public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    window = std::make_unique<MainWindow>(nullptr, data);
    window->Show(true);
    return true;
}