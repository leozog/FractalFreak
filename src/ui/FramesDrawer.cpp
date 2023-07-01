#include "ui/FramesDrawer.h"

FramesDrawer::FramesDrawer(AppData &data, wxPanel *m_fractalPanel) : data{data}, m_fractalPanel{m_fractalPanel}, mode{Mode::Idle}, current_frame{0}, stop{false}
{
    drawing_thread = std::thread(FramesDrawer::draw_loop, this);
}

FramesDrawer::~FramesDrawer()
{
    stop = true;
    drawing_thread.join();
}

void FramesDrawer::draw(double fps, Mode mode)
{
    this->fps = fps;
    this->current_frame = 0;
    this->mode = mode;
}

void FramesDrawer::draw_loop()
{
    auto start = std::chrono::steady_clock::now();
    while (true)
    {
        if (stop)
            break;

        if (data.animation)
        {
            uint32_t n = data.animation->n_frames();
            if (mode == Mode::Render)
            {
                current_frame = data.animation->n_frames_ready();
                drawFrame(data.animation->get_frame_latest());
            }
            else if (mode == Mode::View)
            {
                if (current_frame < n)
                {
                    drawFrame(data.animation->get_frame_x(current_frame));
                    current_frame++;
                }
                else
                {
                    drawFrame(data.animation->get_frame_latest());
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::microseconds((long long int)(1E6 / fps)) - (std::chrono::steady_clock::now() - start));
        start = std::chrono::steady_clock::now();
    }
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
