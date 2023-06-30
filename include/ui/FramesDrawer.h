#pragma once
#include "ff/Animation.h"
#include "AppData.h"

#include <thread>
#include <chrono>
#include <wx/panel.h>
#include <wx/image.h>
#include <wx/dc.h>
#include <wx/dcbuffer.h>

class MainWindow;

class FramesDrawer
{
public:
    enum Mode
    {
        Render,
        View
    };

private:
    const AppData &data;
    wxPanel *m_fractalPanel;
    bool stop;
    bool end;

public:
    FramesDrawer(AppData &data, wxPanel *m_fractalPanel);
    ~FramesDrawer();
    void draw(double fps, Mode mode, MainWindow *callback = nullptr);

private:
    void clear();
    void drawRender(double fps);
    void drawView(double fps, MainWindow *callback);
    void drawFrame(std::shared_ptr<wxImage> img);
};
