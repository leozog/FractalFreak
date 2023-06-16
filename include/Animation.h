#pragma once
#include <vector>
#include <thread>
#include "Frame.h"
#include "Path.h"

class Animation
{
public:
    const double fps;        // frames per second
    const uint32_t n_frames; // frames per second
private:
    std::vector<Frame> frames; // frames of the animation

    const Path path; // path of animation describing the state of paramethers in every frame

    const uint32_t n_threads;         // number of treads used to render the animation
    std::vector<std::thread> threads; // vector containing invoked threads

public:
    Animation(double fps, uint32_t n_threads, Path path);
    void render();

    wxImage *get_frame_latest() const; // returns latest ready frame
    wxImage *get_frame_x() const;      // returns frame number x
private:
    void process_frames();
};

Animation::Animation(double fps, uint32_t n_threads, Path path) : fps{fps}, n_frames{path.time() * fps}, n_threads{n_threads}
{
}

void Animation::render()
{
    frames.clear();
    frames.reserve(n_frames);
    for (int i = 0; i < n_frames; i++) // creation of every frame, alacation of memory, setting of parameters for this point in time
        frames.push_back(Frame(, path.get_param(static_cast<double>(i) / fps)));

    for (int i = 0; i < n_threads; i++) // invoking the threads
        threads.push_back(std::thread(&Animation::process_frames, &this));

    for (auto &th : threads)
        th.join();
}

void Animation::process_frames();
{
    for (auto &fr : frames)
    {
        if (fr.is_idle())
        {
            fr.set_taken();
            fr.render();
            fr.set_ready();
        }
    }
}

wxImage *Animation::get_frame_latest() const;
{
    for (int i = frames.size() - 1; i >= 0; i--)
    {
        if (frames[i].is_ready())
            return frames[i].get_bitmap();
    }
    return nullptr;
}

wxImage *Animation::get_frame_x() const
{
    if (frames[x].is_ready())
        return frames[x].get_bitmap();
    return nullptr;
}