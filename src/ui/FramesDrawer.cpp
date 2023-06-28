#include "ui/FramesDrawer.h"

FramesDrawer::FramesDrawer(AppData &data, wxPanel *m_fractalPanel) : data{data}, m_fractalPanel{m_fractalPanel}, stop{false}, end{true}
{
}

FramesDrawer::~FramesDrawer()
{
    clear();
}

void FramesDrawer::draw(double fps, Mode mode)
{
    clear();
    if (mode == Mode::Render)
    {
        std::thread t(&FramesDrawer::drawRender, this, fps);
        t.detach();
    }
    else if (mode == Mode::View)
    {
        std::thread t(&FramesDrawer::drawView, this, fps);
        t.detach();
    }
}

void FramesDrawer::clear()
{
    stop = true;
    while (!end)
        ;
    stop = false;
    end = false;
}

void FramesDrawer::drawRender(double fps)
{
    uint32_t n = data.animation->n_frames();
    auto start = std::chrono::steady_clock::now();
    while (data.animation->n_frames_ready() != n)
    {
        if (stop)
            break;
        drawFrame(data.animation->get_frame_latest());
        std::this_thread::sleep_for(std::chrono::microseconds((long long int)(1E6 / fps)) - (std::chrono::steady_clock::now() - start));
        start = std::chrono::steady_clock::now();
    }
    drawFrame(data.animation->get_frame_latest());
    end = true;
}

void FramesDrawer::drawView(double fps)
{
    uint32_t n = data.animation->n_frames();
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++)
    {
        if (stop)
            break;
        drawFrame(data.animation->get_frame_x(i));
        std::this_thread::sleep_for(std::chrono::microseconds((long long int)(1E6 / fps)) - (std::chrono::steady_clock::now() - start));
        start = std::chrono::steady_clock::now();
    }
    end = true;
}

void FramesDrawer::drawFrame(std::shared_ptr<wxImage> img)
{
    // init
    wxClientDC dc1(m_fractalPanel);
    wxBufferedDC dc(&dc1);

    int width, height;
    m_fractalPanel->GetSize(&width, &height);

    dc.DestroyClippingRegion();
    dc.SetClippingRegion(0, 0, width, height);

    // draw black bg
    dc.SetBackground(*wxBLACK_BRUSH);
    dc.Clear();

    // draw frame
    dc.DrawBitmap(wxBitmap(*img), 0, 0);
}
