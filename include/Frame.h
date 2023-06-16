#pragma once

class Frame
{
private:
    enum State
    {
        idle,
        taken,
        ready
    };

    State state;
    const FractalGenerator &fractal;
    const Parameters fractal_parameters;
    const Camera camera;

public:
    Frame();
    void render();              // renders the frame
    wxImage get_bitmap() const; // returns a wxwidgets wxImage

    // (used for multithreading)
    bool is_idle() const;  // checks if the frame is being processed. Returns true if idle
    void set_taken();      // signal that the frame is being processed
    bool is_ready() const; // checks if the frame is ready. Returns true if ready
    void set_ready();      // signal that the frame is ready
};

Frame::Frame() : state{State::idle}
{
}

bool Frame::is_idle() const
{
    return state == State::idle;
}

void Frame::set_taken();
{
    state = State::taken;
}

bool Frame::is_ready() const
{
    return state == State::ready;
}

void Frame::set_ready();
{
    state = State::ready;
}