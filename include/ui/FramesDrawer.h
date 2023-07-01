#pragma once
#include "ff/Animation.h"
#include "AppData.h"

#include <thread>
#include <chrono>
#include <functional>
#include <wx/panel.h>
#include <wx/image.h>
#include <wx/dc.h>
#include <wx/dcbuffer.h>

class FramesDrawer
{
public:
    enum Mode
    {
        Idle,
        Render,
        View
    };
    uint32_t current_frame;

private:
    const AppData &data;
    wxPanel *m_fractalPanel;
    Mode mode;
    double fps;

    std::thread drawing_thread;
    bool stop;

public:
    FramesDrawer(AppData &data, wxPanel *m_fractalPanel);
    ~FramesDrawer();
    void draw(double fps, Mode mode);

private:
    void draw_loop();
    void drawFrame(std::shared_ptr<wxImage> img);
};
